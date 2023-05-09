import csv
import tkinter as tk
from tkinter import ttk
from datetime import datetime

# GUI 생성
root = tk.Tk()
root.title("체중 기록")

# 레이블 생성
weight_label = ttk.Label(root, text="체중(kg):")
weight_label.grid(row=0, column=0)

# 체중 입력 상자 생성
weight_entry = ttk.Entry(root)
weight_entry.grid(row=0, column=1)

# 입력 버튼 클릭 시 실행되는 함수
def save_weight():
    # 입력된 체중과 시간 정보 가져오기
    weight = weight_entry.get()
    now = datetime.now()
    date_time = now.strftime("%Y/%m/%d %H:%M:%S")

    # CSV 파일에 체중과 시간 정보 저장
    with open('weight.csv', mode='a', newline='') as file:
        writer = csv.writer(file)
        writer.writerow([date_time, weight])

    # 입력 상자 초기화
    weight_entry.delete(0, 'end')

# 저장 버튼 생성
save_button = ttk.Button(root, text="저장", command=save_weight)
save_button.grid(row=1, column=0, columnspan=2)

# GUI 실행
root.mainloop()
