import sys
import csv
from PyQt5.QtWidgets import QApplication, QWidget, QLabel, QLineEdit, QPushButton, QVBoxLayout, QHBoxLayout, QComboBox

class InputWindow(QWidget):
    def __init__(self):
        super().__init__()
        
        # GUI 구성 요소 생성
        self.date_label = QLabel("날짜")
        self.date_label.setFont(self.set_font(18))
        self.date_entry = QLineEdit()
        self.category_label = QLabel("분류")
        self.category_label.setFont(self.set_font(18))
        self.category_combo = QComboBox()
        self.category_combo.setFont(self.set_font(18))
        self.category_combo.addItems(["수입", "지출"])
        self.label_label = QLabel("내용")
        self.label_label.setFont(self.set_font(18))
        self.label_entry = QLineEdit()
        self.label_entry.setFont(self.set_font(18))
        self.amount_label = QLabel("금액")
        self.amount_label.setFont(self.set_font(18))
        self.amount_entry = QLineEdit()
        self.amount_entry.setFont(self.set_font(18))
        self.memo_label = QLabel("메모")
        self.memo_label.setFont(self.set_font(18))
        self.memo_entry = QLineEdit()
        self.memo_entry.setFont(self.set_font(18))
        self.submit_button = QPushButton("저장")
        self.submit_button.setFont(self.set_font(18))
        
        # 레이아웃 설정
        form_layout = QVBoxLayout()
        input_layout = QHBoxLayout()
        input_layout.addWidget(self.date_label)
        input_layout.addWidget(self.date_entry)
        form_layout.addLayout(input_layout)
        input_layout = QHBoxLayout()
        input_layout.addWidget(self.category_label)
        input_layout.addWidget(self.category_combo)
        form_layout.addLayout(input_layout)
        input_layout = QHBoxLayout()
        input_layout.addWidget(self.label_label)
        input_layout.addWidget(self.label_entry)
        form_layout.addLayout(input_layout)
        input_layout = QHBoxLayout()
        input_layout.addWidget(self.amount_label)
        input_layout.addWidget(self.amount_entry)
        form_layout.addLayout(input_layout)
        input_layout = QHBoxLayout()
        input_layout.addWidget(self.memo_label)
        input_layout.addWidget(self.memo_entry)
        form_layout.addLayout(input_layout)
        form_layout.addWidget(self.submit_button)
        
        self.setLayout(form_layout)
        self.setWindowTitle("수입/지출 관리 프로그램")
        
        # 버튼 이벤트 설정
        self.submit_button.clicked.connect(self.save_data)
    
    # 폰트 설정 함수
    def set_font(self, size):
        font = self.font()
        font.setPointSize(size)
        return font
        
    # 입력 데이터 처리
    def save_data(self):
        date = self.date_entry.text()
        category = self.category_combo.currentText()
        label = self.label_entry.text()
        amount = self.amount_entry.text()
        memo = self.memo_entry.text()

        # csv 파일에 저장
        with open('data.csv', mode='a', newline='') as file:
            writer = csv.writer(file)
            writer.writerow([date, category, label, amount, memo])

        # 입력한 데이터 초기화
        self.date_entry.setText("")
        self.label_entry.setText("")
        self.amount_entry.setText("")
        self.memo_entry.setText("")

if __name__ == '__main__':
    app = QApplication(sys.argv)
    input_window = InputWindow()
    input_window.show()
    sys.exit(app.exec_())
