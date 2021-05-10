.text

main:
.globl main  

la a3, array_length                             # загрузили адрес array_length
lw a3, 0(a3) 					# загрузили длину массива в регистр a3 

addi a3, a3, -1 				# n-1
la a6, array 					# указатель
li a2, 0  					# i - первый итератор = 0 

loop1: 
	la a6, array 				# загрузили указатель
	li a4, 0 				# j - второй итератор = 0
	loop2:
	bltu a3, a4, loop2_exit 	       # if( n-1 < j ) goto loop2_exit
		lw t2, 0(a6)			# t2 = a[j]
		lw t3, 4(a6)			# t3 = a[j+1]
	
		bltu t2,t3,loop2_exit        # if( a[j] < a[j+1] ) -> loop2_exit
		
		sw t3, 0(a6)			# свап двух элементов
		sw t2, 4(a6) 
		loop2_exit:
			addi a6, a6, 4  	# указатель * 4 
			addi a4, a4, 1  	# второй итератор + 1 
			bltu a4, a3, loop2    # if ( j < n-1) go to loop2
		
	loop1_exit:
		addi a2, a2, 1 		# увеличиваем первый итератор
		bltu a2, a3, loop1           # if( i < n-1 ) goto loop1	
loop_main_exit: 
	finish:
		li a0, 10 			# x0 = 10
		ecall 				# ecall при значении x10 = 10 => останов симулятора

.rodata
	array_length:
	.word 10
.data
	array:
	.word 3,4,1,2,5,6,7,0,8,9
