asect  0x00

# =================================
# INSERT YOUR CODE BELOW
# Executable instructions only
# No dc or ds pseudo-instructions
# Do not include a halt instruction: that has been done already (below)
# ---------------------------------------------------------------------
    ldi r0, aLo
    ld r0, r0

	ldi r1, aHi
	ld r1, r1

    ldi r2, bLo
    ld r2, r2

	ldi r3, bHi
	ld r3, r3
	
	jsr minus
	jsr minus


# =================================
# LEAVE THIS PART OF THE FILE ALONE
# Do not change the next two instructions: they must be the last two
# instructions executed by your program.
    ldi r2, resLo  # Loads the start address of your result into r0 for the robot
	st r2, r0
	
	ldi r3, resHi
	st r3, r1
    halt           # Brings execution to a halt

# =================================
# DATA GOES BELOW
# We have set this up for you, but you will need to test your program by
# compiling and running it several times with different input data values
# (different bit-strings placed at addresses aLo, aHi, bLo and bHi)
# ---------------------------------------------------------------------

minus:
	push r2
	push r3
	
	if
		cmp r0, r2
	is lo
		dec r1
	fi
	
	sub r0, r2
	sub r1, r3
	
	move r2, r0
	move r3, r1
	
	pop r3
	pop r2
	rts

INPUTS>
aLo:	dc	0b00000010 	# replace 0 by your choice of low byte for testing
aHi:	dc	0b10000000 	# replace 0 by your choice of high byte for testing
bLo:	dc	0b00000100 	# replace 0 by your choice of low byte for testing
bHi:	dc	0b00000001	# replace 0 by your choice of high byte for testing
ENDINPUTS>

resLo:	ds	1
resHi:  ds  1		# two bytes reserved for the result
end


