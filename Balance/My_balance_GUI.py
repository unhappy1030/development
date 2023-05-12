import sqlite3
import matplotlib.pyplot as plt

conn = sqlite3.connect('transactions.db')

def plot_transactions():
    c = conn.cursor()
    c.execute("SELECT SUM(amount) FROM transactions WHERE amount > 0")
    income = c.fetchone()[0]
    c.execute("SELECT SUM(amount) FROM transactions WHERE amount < 0")
    expense = c.fetchone()[0]
    balance = income + expense

    labels = ['Income', 'Expense', 'Balance']
    values = [income, expense, balance]
    plt.pie(values, labels=labels, autopct='%1.1f%%')
    plt.axis('equal')
    plt.show()
    
if __name__ == '__main__':
    plot_transactions()