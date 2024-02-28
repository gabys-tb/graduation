# Trabalho final de Programação e Desenvolvimento de Software II

**Membros do grupo:**
- Arthur Linhares Madureira
- Gabriel Pains de Oliveira Cardoso
- Gabriela Tavares Barreto
- Philipe Dutra Cunha
- Rodrigo Sales Nascimento



**Mini plataforma de streaming de músicas**

Este trabalho consiste de uma pequena plataforma executada por terminal, contendo funções básicas que se assemelham a uma plataforma de streaming de músicas. Há dois tipos de conta: Usuário e Artista.

Usuários e Artistas podem:
- Pesquisar Tracks e Albums
- Tocar Tracks e Albums

Apenas os Usuários podem:
- Criar Playlists
- Deletar suas Playlists
- Adicionar Tracks as suas Playlists
- Deletar Tracks de suas Playlists
- Ver suas Playlists
- Tocar suas Playlists

Apenas os Artistas podem:
- Adicionar Tracks à plataforma
- Adicionar Albums à plataforma
- Ver seus Albums
- Tocar seus Albums

Instruções para compilação:
É possível compilar o Spotlite para Windows ou Linux sem nenhum requerimento adicional. No entanto, pelo uso de cores no terminal por meio de ANSI escape codes e alguns símbolos nos textos, é recomendado executar o Spotlite em sistemas Linux para a melhor experiência de usuário. Também é necessária permissão para o executável criar/deletar e ler/escrever arquivos.

O trabalho acompanha um Makefile com as seguintes opções:

- make: Compila os arquivos source em .o e gera um executável
- make DEBUG=YES: Compila os arquivos source em .o e gera um executável com flags de depuração
- make run: Roda o executável gerado
- make valgrind: Roda o executável gerado a partir do valgrind a fim de verificar memory leaks
- make tests: Compila os arquivos source de testes em .o e gera um executável com flags de coverage
- make runtests: Roda o executável de testes gerado
- make coverage: Roda o executável de testes por padrão e em seguida, roda gcovr a fim de verificar o coverage do código
- make clean: Limpa os arquivos .o e o executável gerado, também limpa os arquivos .o de testes e seu executável
