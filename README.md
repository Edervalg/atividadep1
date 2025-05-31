-Sistema de Controle de Peças de Fábrica
📌 Visão Geral
Este programa em C permite gerenciar o cadastro de peças em uma fábrica, armazenando os dados em arquivos binários. O sistema oferece operações completas de CRUD (Create, Read, Update, Delete) e geração de relatórios por setor.

🛠️ Pré-requisitos
Compilador GCC instalado

Sistema operacional Linux/Windows/macOS

Terminal para execução

⚙️ Instalação e Execução
Compilação
bash
gcc fabrica_pecas.c -o fabrica
Execução
bash
./fabrica
📋 Menu de Opções
O sistema apresenta um menu com as seguintes funcionalidades:

Cadastrar peça

Registra novas peças com:

Código automático

Nome e descrição

Setor (Montagem/Usinagem/Acabamento/Embalagem)

Quantidade, peso e data de fabricação

Listar todas as peças

Exibe em formato de tabela:

Código, nome, setor

Quantidade, peso e data

Buscar peça por código

Localiza uma peça específica

Mostra todos os detalhes cadastrados

Atualizar peça

Permite modificar qualquer informação

Mantém o código original

Remover peça

Exclui permanentemente um registro

Usa arquivo temporário para segurança

Relatório por setor

Filtra peças por setor

Calcula totais e peso agregado

📁 Estrutura de Arquivos
pecas.bin: Arquivo binário principal (criado automaticamente)

temp.bin: Arquivo temporário (usado durante remoções)

⚠️ Observações Importantes
O programa usa arquivos binários para persistência dos dados

Todos os campos são validados durante a entrada

A remoção é feita de forma segura (cria novo arquivo sem o registro)

Os códigos são gerados automaticamente e não se repetem

📊 Exemplo de Uso
Cadastre várias peças de diferentes setores

Liste as peças para verificar o cadastro

Gere relatórios por setor específico

Atualize quantidades quando necessário

Remova peças que não estão mais em produção



