import random
import gym
import numpy as np
import tensorflow as tf

# 하이퍼파라미터 설정
ENV_NAME = 'CartPole-v1'  # 환경 이름
GAMMA = 0.99  # 감마
EPSILON_START = 1.0  # 시작 엡실론
EPSILON_END = 0.1  # 최종 엡실론
EPSILON_DECAY = 1000  # 엡실론 감소 속도
MEMORY_CAPACITY = 10000  # 메모리 용량
BATCH_SIZE = 32  # 배치 사이즈
TRAIN_START = 1000  # 학습 시작 지점
TARGET_UPDATE_INTERVAL = 1000  # 타겟 네트워크 업데이트 간격

# 환경 설정
env = gym.make(ENV_NAME)
obs_size = env.observation_space.shape[0]
n_actions = env.action_space.n

# 네트워크 구성
model = tf.keras.models.Sequential([
    tf.keras.layers.Dense(64, activation='relu', input_shape=(obs_size,)),
    tf.keras.layers.Dense(64, activation='relu'),
    tf.keras.layers.Dense(n_actions + 1, activation=None)
])

# 손실 함수와 옵티마이저 설정
loss_fn = tf.keras.losses.MeanSquaredError()
optimizer = tf.keras.optimizers.Adam(learning_rate=1e-3)

# 타겟 네트워크 설정
target_model = tf.keras.models.clone_model(model)
target_model.set_weights(model.get_weights())

# 메모리 설정
memory = []

# 엡실론 설정
epsilon = EPSILON_START

# 총 보상을 기록할 리스트
total_rewards = []

# 에피소드 반복문
for episode in range(1000):
    obs = env.reset()
    done = False
    total_reward = 0
    # 타임스텝 반복문
    while not done:
        # 엡실론 그리디 액션 선택
        if np.random.rand() < epsilon:
            action = env.action_space.sample()
        else:
            q_values = model.predict(np.array(obs).reshape(1, -1))
            action = np.argmax(q_values[0])
        assert env.action_space.contains(action)
        # 다음 상태, 보상, 종료 여부를 얻음
        next_obs, reward, done, _, info = env.step(action)

        # 메모리에 저장
        memory.append((obs, action, reward, next_obs, done))

        # 메모리 용량이 넘치면 가장 오래된 데이터를 삭제
        if len(memory) > MEMORY_CAPACITY:
            memory.pop(0)

        # 샘플링하여 학습
        if len(memory) > TRAIN_START:
            minibatch = random.sample(memory, BATCH_SIZE)

            obs_batch = np.array([m[0] for m in minibatch])
            action_batch = np.array([m[1] for m in minibatch])
            reward_batch = np.array([m[2] for m in minibatch])
            next_obs_batch = np.array([m[3] for m in minibatch])
            done_batch = np.array([m[4] for m in minibatch])

            # 타겟 값 계산
            next_q_values = target_model.predict(next_obs_batch)
            max_next_q_values = np.max(next_q_values, axis=1)
            target_q_values = reward_batch + (1 - done_batch) * GAMMA * max_next_q_values

            # 타겟 값으로 학습
            with tf.GradientTape() as tape:
                state_batch = np.array(obs_batch[0])
                action_batch = np.array(obs_batch[1])
                next_state_batch = np.array(obs_batch[2])
                reward_batch = np.array(obs_batch[3])
                done_batch = np.array(obs_batch[4])

                # 변환된 데이터를 모델에 입력합니다.
                q_values = model([state_batch, action_batch, next_state_batch, reward_batch, done_batch])
                action_indices = tf.stack([tf.range(BATCH_SIZE), action_batch], axis=1)
                q_values = tf.gather_nd(q_values, action_indices)
                loss = loss_fn(target_q_values, q_values)

            grads = tape.gradient(loss, model.trainable_variables)
            optimizer.apply_gradients(zip(grads, model.trainable_variables))

        # 타겟 네트워크 업데이트
        if episode % TARGET_UPDATE_INTERVAL == 0:
            target_model.set_weights(model.get_weights())

        obs = next_obs
        total_reward += reward

    # 엡실론 감소
    epsilon = EPSILON_END + (EPSILON_START - EPSILON_END) * np.exp(-episode / EPSILON_DECAY)

    total_rewards.append(total_reward)

    print(f"Episode: {episode + 1}, Total reward: {total_reward:.0f}, Average reward: {np.mean(total_rewards[-100:]):.1f}")

# 모델 저장
model.save('dqn.h5')

# 총 보상 그래프 출력
import matplotlib.pyplot as plt
plt.plot(total_rewards)
plt.xlabel('Episode')
plt.ylabel('Total reward')
plt.show()
