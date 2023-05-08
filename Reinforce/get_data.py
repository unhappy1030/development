import win32com.client
import pandas as pd
import time

# COM 오브젝트 생성
instStockChart = win32com.client.Dispatch("CpSysDib.StockChart")

# 입력 값 세팅
instStockChart.SetInputValue(0, 'A005930') # 종목 코드 - 삼성전자
instStockChart.SetInputValue(1, ord('2')) # 요청 구분 - 1: 기간, 2: 개수
instStockChart.SetInputValue(4, 100) # 요청 개수
instStockChart.SetInputValue(5, [0, 1, 2, 3, 4, 5, 6, 8]) # 요청 필드 - 0: 날짜, 1: 시간, 2: 시가, 3: 고가, 4: 저가, 5: 종가, 6: 거래량, 8: 거래대금
instStockChart.SetInputValue(6, ord('m')) # 차트 구분 - m: 분봉, D: 일봉, W: 주봉, M: 월봉
instStockChart.SetInputValue(9, ord('1')) # 수정 주가 사용 여부 - 0: 미사용, 1: 사용

# 데이터 요청
instStockChart.BlockRequest()

# 데이터 수신
numData = instStockChart.GetHeaderValue(3) # 수신된 데이터 개수
numField = instStockChart.GetHeaderValue(1) # 수신된 필드 개수

data = [] # 수신된 데이터를 저장할 리스트

for i in range(numData):
    row = [] # 각 데이터를 저장할 리스트
    for j in range(numField):
        value = instStockChart.GetDataValue(j, i) # j번째 필드의 i번째 데이터
        row.append(value)
    data.append(row)

# 데이터를 DataFrame 형식으로 변환
df = pd.DataFrame(data, columns=['date', 'time', 'open', 'high', 'low', 'close', 'volume', 'amount'])

# 날짜와 시간을 합쳐 datetime 형식으로 변환
df['datetime'] = pd.to_datetime(df['date'].astype(str) + df['time'].astype(str), format='%Y%m%d%H%M%S')

# 필요한 열만 선택
df = df[['datetime', 'open', 'high', 'low', 'close', 'volume', 'amount']]

# 데이터 출력
print(df)