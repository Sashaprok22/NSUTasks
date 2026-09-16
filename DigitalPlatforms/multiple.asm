asect 0
ldi r0, a
ldi r1, b
jsr mult_r0_r1

halt

move_r0_counter:
	push r1
	push r2
	push r3
	
	ldi r1, 4
	ldi r2, counter
	move_loop:
		tst r1
		bz move_loop_end
		
		ld r0, r3
		st r2, r3
		inc r2
		inc r0
		dec r1
		br move_loop

	move_loop_end:
		ldi r3, 4
		sub r0, r3
		move r3, r0
		pop r3
		pop r2
		pop r1
		rts
		
clear_mult_vars:
	push r0
	push r1
	push r2
	push r3
	
	ldi r0, counter+4
	ldi r1, result+4
	ldi r2, 0
	
	clear_loop:
		dec r0
		dec r1
		st r0, r2
		st r1, r2
		
		ldi r3, counter
		cmp r3, r0
		bz stop_clear
		br clear_loop
	
	stop_clear:
		pop r3
		pop r2
		pop r1
		pop r0
		rts
		

mult_r0_r1:
	push r2
	push r3
	
	jsr clear_mult_vars
	
	jsr move_r0_counter
	
	sub_counter:
		push r2
		push r3
		ldi r2, counter+4
		
		counting:
			ldi r3, counter
			dec r2
			cmp r2, r3
			bz full_end
			
			ld r2, r3
			dec r3
			st r2, r3
			bcs counting
			br end_counting
			
		end_counting:
			pop r3
			pop r2
			br add_result
		
		full_end:
			pop r3
			pop r2
			br end_mult
		
	add_result:
		push r0
		push r1
		push r2
		push r3
		
		ldi r3, result+3
		ldi r2, 3
		add r2, r1
		ldi r0, 0
		
		adding:
			push r0
			ldi r0, result
			cmp r3, r0
			pop r0
			bz end_adding
			shr r0 # Гениальный мув на изменение Carry
			
			ld r3, r2
			ld r1, r0
			addc r2, r0
			st r3, r0
			
			ldi r0, 0
			bcc adding_without_carry
			ldi r0, 1
		
			adding_without_carry:
				dec r3
				dec r1
				br adding
		
		end_adding:
			pop r3
			pop r2
			pop r1
			pop r0
			br sub_counter
			
	end_mult:
		pop r3
		pop r2
		rts

a: dc 0x00, 0x00, 0x00, 0x0C
b: dc 0x00, 0x00, 0x00, 0x0C
result: ds 4

# temp vars
counter: ds 4
end