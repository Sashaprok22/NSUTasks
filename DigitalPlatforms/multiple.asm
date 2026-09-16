asect 0

ldi r1, a
ldi r2, b
jsr mult_r1_r2

halt

mult_r1_r2:
	ld r1, r0
	push r0
	
	inc r1
	ld r1, r0
	push r0
	dec r1
	
	start_loop:
		pop r0
		dec r0
		bcs high_sub
		push r0
		br main_loop
	
	high_sub:
		pop r3
		dec r3
		bcs end_loop
		push r3
		push r0
		br main_loop
		
	main_loop:
		ldi r0, result+1
		ld r0, r0
		inc r2
		ld r2, r3
		dec r2

		add r0, r3
		
		ldi r0, result+1
		st r0, r3
		
		ldi r0, result
		ld r0, r0
		ld r2, r3
		
		addc r0, r3
		
		ldi r0, result
		st r0, r3
		
		br start_loop
			
	end_loop:
		rts
		
	
	rts

a: dc 1, 1
b: dc 2, 3
result: ds 2
end