import sqlite3
from datetime import datetime
import matplotlib.pyplot as plt


class MyBalance:
    def __init__(self):
        self.conn = sqlite3.connect("account_book.db")
        self.create_table()
        self.update_display()

    def create_table(self):
        c = self.conn.cursor()
        c.execute('''CREATE TABLE IF NOT EXISTS account_book
            (type TEXT,
             date TEXT,
             label TEXT,
             category TEXT,
             amount INTEGER
             )''')
        self.conn.commit()

    def add_income(self, date, category, amount, memo=''):
        c = self.conn.cursor()
        c.execute("INSERT INTO account_book VALUES (?, ?, ?, ?, ?, ?)", (date, category, int(amount), int(amount), 0, memo))
        self.conn.commit()
        self.update_display()

    def add_expense(self, date, category, amount, memo=''):
        c = self.conn.cursor()
        c.execute("INSERT INTO account_book VALUES (?, ?, ?, ?, ?, ?)", (date, category, int(amount), 0, int(amount), memo))
        self.conn.commit()
        self.update_display()

    def update_display(self):
        c = self.conn.cursor()
        c.execute("SELECT category, SUM(amount) FROM account_book WHERE type = 'income' GROUP BY category")
        income = c.fetchall()
        c.execute("SELECT category, SUM(amount) FROM account_book WHERE type = 'expense' GROUP BY category")
        expense = c.fetchall()
        balance = income - expense

        print(f"수입: {income:,d}원, 지출: {expense:,d}원, 잔액: {balance:,d}원")
    def plot_expenses(self):
        c = self.conn.cursor()
        c.execute("SELECT category, SUM(amount) FROM account_book WHERE type = 'expense' GROUP BY category")
        results = c.fetchall()
        categories, amounts = zip(*results)
        
        plt.pie(amounts, labels=categories, autopct='%1.1f%%')
        plt.title('Monthly Expenses')
        plt.show()
    def close(self):
        self.conn.close()


if __name__ == '__main__':
    balance = MyBalance()
    while True:
        print("="*30)
        print("1. 수입 추가")
        print("2. 지출 추가")
        print("3. 현재 잔고 상태")
        print('4. 그래프 보기')
        print('5. 종료')
        print("="*30)
        choice = input("원하는 기능을 선택하세요: ")
        if choice == '1':
            date = datetime.today().strftime('%Y-%m-%d')
            category = input("수입 카테고리를 입력하세요: ")
            amount = input("수입 금액을 입력하세요: ")
            memo = input("메모를 입력하세요 (없으면 엔터): ")
            balance.add_income(date, category, amount, memo)
        elif choice == '2':
            date = datetime.today().strftime('%Y-%m-%d')
            category = input("지출 카테고리를 입력하세요: ")
            amount = input("지출 금액을 입력하세요: ")
            memo = input("메모를 입력하세요 (없으면 엔터): ")
            balance.add_expense(date, category, amount, memo)
        elif choice == '3':
            balance.update_display()
        elif choice == '4':
            balance.plot_expenses()
        elif choice == '5':
            balance.close()
            print("프로그램을 종료합니다.")
            break
        else:
            print("잘못된 입력입니다. 다시 선택해주세요.")
