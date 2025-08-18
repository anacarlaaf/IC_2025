import pandas as pd
# 435666 1057066 
# Nome do arquivo de entrada e saída
arquivo_entrada = 'USA-road-d.txt'
arquivo_saida = 'USA-road-d_cleaned.csv'

# Número da coluna a ser removida (começando em 0)
coluna_para_excluir = 0  # exemplo: terceira coluna

# Ler o arquivo (ajuste o separador conforme necessário
dados = pd.read_csv(arquivo_entrada, sep=' ', header=None)

# Excluir a coluna
dados = dados.drop(dados.columns[coluna_para_excluir], axis=1)

# Salvar o resultado
dados.to_csv(arquivo_saida, sep=' ', index=False, header=False)