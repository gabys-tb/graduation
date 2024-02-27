.data
cartao: .word 4 9 1 6 6 4 1 8 5 9 3 6 9 0 8 0
##### START MODIFIQUE AQUI START #####
#
# Este espaço eh para você definir as suas constantes e vetores auxiliares.
##### END MODIFIQUE AQUI END #####
.text
main:
la a0, cartao
jal ra, verifica
beq zero,zero,FIM
##### START MODIFIQUE AQUI START #####
verifica:
    addi x5, x0, 4
    sub x2, x2, x5 
    sw x1, (0)x2
    jal ra, multvetores
    lw x1, (0)x2   # recupera o endereço de retorno da pilha
    addi x2, x2, 4   # sobe apontador da pilha     
    addi x5, x0, 10 # x5 = 10
    div x5, a1, x5 # x5 = total/10
    addi x7, x0, 10
    mul x5, x5, x7 # x5 = x5*10
    sub x5, a1, x5 # x5 = total - x5 = resto
    sub x5, x7, x5
    beq x5, x7, caso10
continua_verifica:
	lw x6, (0)a0 # x6 = *cartao[15]
    addi a0, x0, 1 
    beq x6, x5, exit_verifica # x6 == resto? exit : continua
    addi a0, x0, 0 # atualiza variavel de retorno para falso
exit_verifica: 
	jalr zero, 0(ra)
caso10: 
	addi x5, x0, 0
    beq x0, x0, continua_verifica
    
multvetores:
    addi x6, x0, 0 # x6 = 0 -> x6 = total
    addi x7, x0, 0 # x7 guarda indice do vetor
    addi x28, x0, 16 # x28 = 16
    addi x29, x0, 10 # x29 = 10
L1: lw x5, 0(a0) # x5 recebe vetor[i]
    addi x7, x7, 1 # x7++
    slli x5, x5, 1 # multiplica x5 por 2
    blt x5, x29, soma # se valor calculado < 10, ent pode soma-lo ao valor total
	div x30, x5, x29 # x30 = x5/10 = quociente
	sub x5, x5, x29 # x5 = resto de x5/10
    add x5, x5, x30 # soma digitos originais de x5
soma:    
	add x6, x6, x5 # total+=x5;
    addi a0, a0, 4 # calcula prox endereço
    addi x7, x7, 1 # x7++
    beq x7, x28, exit_mult # x7 == 16? exit : continua
    lw x5, 0(a0) #x5 recebe novo valor
    add x6, x6, x5 # total+=x5;
    addi a0, a0, 4 # calcula prox endereço
    beq x0, x0, L1 # continua no loop
exit_mult: 
    add a1, x6, x0 # a1 recebe valor total
    jalr zero, 0(ra) 
##### END MODIFIQUE AQUI END #####
FIM: add zero, zero, zero