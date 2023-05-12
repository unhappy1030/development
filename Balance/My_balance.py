import sys
import sqlite3
from PyQt5.QtWidgets import QApplication, QWidget, QLabel, QLineEdit, QComboBox, QPushButton, QMessageBox, QMainWindow
from PyQt5.QtCore import Qt
from PyQt5.QtGui import *
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
from matplotlib.figure import Figure
import matplotlib.pyplot as plt



class AccountManager(QMainWindow):
    def __init__(self):
        self.create_table()
        super().__init__()
        self.initUI()
        
    def create_table(self):
        with sqlite3.connect(self.db_name) as conn:
            c = conn.cursor()
            c.execute("CREATE TABLE IF NOT EXISTS account_book (date TEXT, category TEXT, amount INTEGER, balance INTEGER, description TEXT, income INTEGER)")

    def initUI(self):
        self.income_label = QLabel(self)
        self.income_label.setText("수입")
        self.income_label.setGeometry(20, 20, 60, 30)

        self.expense_label = QLabel(self)
        self.expense_label.setText("지출")
        self.expense_label.setGeometry(20, 70, 60, 30)

        self.balance_label = QLabel(self)
        self.balance_label.setText("잔액")
        self.balance_label.setGeometry(20, 120, 60, 30)

        self.income_amount_label = QLabel(self)
        self.income_amount_label.setText("합계:")
        self.income_amount_label.setGeometry(110, 20, 60, 30)

        self.expense_amount_label = QLabel(self)
        self.expense_amount_label.setText("합계:")
        self.expense_amount_label.setGeometry(110, 70, 60, 30)

        self.balance_amount_label = QLabel(self)
        self.balance_amount_label.setText("합계:")
        self.balance_amount_label.setGeometry(110, 120, 60, 30)

        self.income_amount_value = QLabel(self)
        self.income_amount_value.setText("0")
        self.income_amount_value.setGeometry(170, 20, 60, 30)

        self.expense_amount_value = QLabel(self)
        self.expense_amount_value.setText("0")
        self.expense_amount_value.setGeometry(170, 70, 60, 30)

        self.balance_amount_value = QLabel(self)
        self.balance_amount_value.setText("0")
        self.balance_amount_value.setGeometry(170, 120, 60, 30)

        self.income_date_label = QLabel(self)
        self.income_date_label.setText("날짜:")
        self.income_date_label.setGeometry(10, 170, 60, 30)

        self.income_date_entry = QLineEdit(self)
        self.income_date_entry.setGeometry(70, 170, 100, 30)

        self.income_category_label = QLabel(self)
        self.income_category_label.setText("분류:")
        self.income_category_label.setGeometry(10, 220, 60, 30)

        self.income_category_combobox = QComboBox(self)
        self.income_category_combobox.setGeometry(70, 220, 100, 30)
        self.income_category_combobox.addItems(["월급", "용돈", "기타"])

        self.income_amount_label = QLabel(self)
        self.income_amount_label.setText("금액:")
        self.income_amount_label.setGeometry(10, 270, 60, 30)

        self.income_amount_entry = QLineEdit(self)
        self.income_amount_entry.setGeometry(70, 270, 100, 30)

        self.add_income_button = QPushButton(self)
        self.add_income_button.setText("수입 추가")
        self.add_income_button.setGeometry(180, 270, 100, 30)
        self.add_income_button.clicked.connect(self.add_income)

       
        self.expense_date_label = QLabel(self)
        self.expense_date_label.setText("날짜:")
        self.expense_date_label.setGeometry(10, 320, 60, 30)

        self.expense_date_entry = QLineEdit(self)
        self.expense_date_entry.setGeometry(70, 320, 100, 30)

        self.expense_category_label = QLabel(self)
        self.expense_category_label.setText("분류:")
        self.expense_category_label.setGeometry(10, 370, 60, 30)

        self.expense_category_combobox = QComboBox(self)
        self.expense_category_combobox.setGeometry(70, 370, 100, 30)
        self.expense_category_combobox.addItems(["식비", "교통비", "문화생활", "기타"])

        self.expense_amount_label = QLabel(self)
        self.expense_amount_label.setText("금액:")
        self.expense_amount_label.setGeometry(10, 420, 60, 30)

        self.expense_amount_entry = QLineEdit(self)
        self.expense_amount_entry.setGeometry(70, 420, 100, 30)

        self.add_expense_button = QPushButton(self)
        self.add_expense_button.setText("지출 추가")
        self.add_expense_button.setGeometry(180, 420, 100, 30)
        self.add_expense_button.clicked.connect(self.add_expense)

        self.graph_button = QPushButton(self)
        self.graph_button.setText("그래프 출력")
        self.graph_button.setGeometry(180, 520, 100, 30)
        self.graph_button.clicked.connect(self.show_graph)

        self.setGeometry(300, 300, 300, 600)
        self.setWindowTitle('가계부')
        self.show()

    def add_income(self):
        date = self.income_date_entry.text()
        category = self.income_category_combobox.currentText()
        amount = self.income_amount_entry.text()
        conn = sqlite3.connect("account_book.db")
        c = conn.cursor()
        if not date or not amount:
            QMessageBox.about(self, "경고", "날짜와 금액을 입력하세요")
        else:
            c.execute("INSERT INTO account_book VALUES (?, ?, ?, ?)", (date, category, int(amount), 0))
            conn.commit()
            conn.close()
            self.income_date_entry.setText("")
            self.income_amount_entry.setText("")
            self.update_display()

    def add_expense(self):
        date = self.expense_date_entry.text()
        category = self.expense_category_combobox.currentText()
        amount = self.expense_amount_entry.text()
        conn = sqlite3.connect("account_book.db")
        c = conn.cursor()
        if not date or not amount:
            QMessageBox.about(self, "경고", "날짜와 금액을 입력하세요")
        else:
            c.execute("INSERT INTO account_book VALUES (?, ?, ?, ?)", (date, category, 0, int(amount)))
            conn.commit()
            conn.close()
            self.expense_date_entry.setText("")
            self.expense_amount_entry.setText("")
            self.update_display()

    def update_display(self):
        conn = sqlite3.connect("account_book.db")
        c = conn.cursor()
        c.execute("SELECT SUM(income) FROM account_book")
        income_sum = c.fetchone()[0]
        if income_sum is None:
            income_sum = 0
        c.execute("SELECT SUM(expense) FROM account_book")
        expense_sum = c.fetchone()[0]
        if expense_sum is None:
            expense_sum = 0
        balance = income_sum - expense_sum
        self.income_amount_value.setText(str(income_sum))
        self.expense_amount_value.setText(str(expense_sum))
        self.balance_amount_value.setText(str(balance))
        conn.commit()
        conn.close()

    def show_graph(self):
        conn = sqlite3.connect("account_book.db")
        c = conn.cursor()
        labels = []
        values = []
        c.execute("SELECT category, SUM(income) AS total_income, SUM(expense) AS total_expense FROM account_book GROUP BY category")
        rows = c.fetchall()
        for row in rows:
            labels.append(row[0])
            values.append(row[1] - row[2])
        plt.bar(labels, values)
        plt.title("분류별 수입/지출 그래프")
        plt.xlabel("분류")
        plt.ylabel("금액")
        plt.show()

if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = AccountManager()
    sys.exit(app.exec_())

