import csv
# import pandas as pd

# df = pd.read_parquet('parquet_novo.parquet')

# print(df)

# df.to_csv('out2.csv', index=False)  

# import duckdb

# print(duckdb.query('''
#   SELECT *
#   EXCLUDE('moipError.original.fundingInstrument.creditCard.holder.birthDate')
#   FROM 'parquet_novo.parquet'
#   ''').fetchall())


import polars as pl

df = pl.read_parquet_schema('20240623-233716484.parquet')

print(df)


# Seu dicionário de dadoss
data = df

# Caminho para o arquivo CSV
csv_file = 'output.csv'

# Obter os nomes das colunas
columns = list(data.keys())

# Escrever os dados em um arquivo CSV
with open(csv_file, mode='w', newline='') as file:
    writer = csv.DictWriter(file, fieldnames=columns)

    # Escrever cabeçalho
    writer.writeheader()

    # Escrever dados
    writer.writerow(data)

