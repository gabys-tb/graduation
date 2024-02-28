.data
vetor: .word 0 0 0 0
##### START MODIFIQUE AQUI START #####
#
# Este espaço eh para você definir as suas constantes e vetores auxiliares.
##### END MODIFIQUE AQUI END #####
.text
main:
add s0, zero, zero
#Teste 1
addi a0, zero, 5
addi a1, zero, 7
la a2, vetor
jal ra, primos
addi t0, zero, 2
beq t0, a0, OK1
beq zero, zero, T2
OK1: addi s0, s0, 1 #Teste ok, passou
#Teste 2
T2: addi a0, zero, 1
addi a1, zero, 6
la a2, vetor
jal ra, primos
addi t0, zero, 3
beq t0, a0, OK2
beq zero, zero, FIM
OK2: addi s0, s0, 1 #Teste ok, passou
beq zero, zero, FIM
##### START MODIFIQUE AQUI START #####
primos: 
	addi x6, x0, 0 # numPrimos = 0
	addi x7, zero, 1 # x7 = 1
    addi x28, x0, 0 # raiz = 0
    beq a0, x7, pula1 # se primeiro numero for 1, n o conta como primo
    
raiz:
    addi x28, x28, 1     # raiz = raiz++
    mul x5, x28, x28    # calcula a raiz ao quadrado
    sub x5, a0, x5      # x5 = x - raiz^2
    bge x5, x0, raiz    # x15 > 0? raiz : continua
    sub x28, x28, x7     # raiz = raiz - x7 = raiz - 1
	addi x29, x0, 2 # divisor = 2

verifica:      
	beq a0, x29, ehprimo  # se a0 = 2, sai do loop
    div x30, a0, x29      # aux = quociente = x / divisor
    mul x30, x30, x29    # aux = quociente * divisor
    sub x30, a0, x30      # resto = x - aux
    beq x30, x0, composto # resto == 0? composto : continua
    addi x29, x29, 1 # divisor++
    bgt x29, x28, ehprimo  # divisor > raiz? é primo! 
    beq x0, x0, verifica
    
termina: 
	addi x10, x6, 0
 	jalr zero, 0(ra)

ehprimo:
	addi x6, x6, 1 # numPrimos++
    sw a0, 0(a2)
    addi a2, a2, 4
composto: 
	addi a0, a0, 1 
    bgt a0, a1, termina
    addi x28, x0, 0 # raiz = 0
    beq x0, x0, raiz
pula1:    
	addi a0, a0, 1
    beq x0, x0, raiz
	    
jalr zero, 0(ra)

##### END MODIFIQUE AQUI END #####
FIM: add zero, zero, zero