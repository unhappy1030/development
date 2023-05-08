import matplotlib.pyplot as plt
import matplotlib.font_manager as fm
from pykrx import stock

def plot_minute_price(code, date):
    df = stock.get_market_ohlcv_by_date(date, date, code, "m")
    minutes = df.index.strftime("%Y-%m-%d %H:%M:%S")
    prices = df['종가']
    plt.plot(minutes, prices)
    plt.title(f'{code} {date} 분봉 그래프')
    plt.xlabel('시간')
    plt.ylabel('종가')
    plt.xticks(rotation=45)
    plt.show()

# 사용 예시
plot_minute_price('005930', '20220504')
