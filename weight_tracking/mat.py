import csv
import matplotlib.pyplot as plt

# 폰트 설정
plt.rc('font', family='NanumGothic', weight='bold', size = 14)

# CSV 파일에서 체중과 시간 정보 가져오기
weights = []
times = []
with open('weight.csv', mode='r') as file:
    reader = csv.reader(file)
    for row in reader:
        time_str = row[0]  # "YYYY-MM-DD hh:mm:ss" 형식의 문자열
        time_label = time_str[:10] + '\n' + time_str[11:]  # "날짜\n시간" 형식의 레이블
        times.append(time_label)
        weights.append(float(row[1]))

# 그래프 그리기
plt.figure(figsize=(20, 10))
plt.plot(times, weights, color='coral', linestyle='-', linewidth=3, marker='.')

plt.xlabel("시간")
plt.ylabel("체중(kg)")
plt.title("체중 기록 그래프", weight='bold')
for i in range(len(weights)):
    plt.text(times[i], weights[i], str(weights[i]), ha='center', va='bottom', fontsize=11)
plt.show()
