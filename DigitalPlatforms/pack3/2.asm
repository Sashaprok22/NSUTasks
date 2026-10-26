asect  0x00

# =================================
# INSERT YOUR CODE BELOW
# Executable instructions only
# No dc or ds pseudo-instructions
# Do not include a halt instruction: that has been done already (below)
# ---------------------------------------------------------------------

# Fst byte
ldi r0, resLo

ldi r1, aLo
ld r1, r1

ldi r2, bLo
ld r2, r2

add r2, r1
st r0, r1

#Scnd byte
ldi r0, resHi

ldi r1, aHi
ld r1, r1

ldi r2, bHi
ld r2, r2

addc r2, r1
st r0, r1




# =================================
# LEAVE THIS PART OF THE FILE ALONE
# Do not change the next two instructions: they must be the last two
# instructions executed by your program.
    ldi r0, resLo  # Loads the start address of your result into r0 for the robot
    halt           # Brings execution to a halt

# =================================
# DATA GOES BELOW
# We have set this up for you, but you will need to test your program by
# compiling and running it several times with different input data values
# (different bit-strings placed at addresses aLo, aHi, bLo and bHi)
# ---------------------------------------------------------------------

INPUTS>
aLo:	dc	0b00101100 	# replace 0 by your choice of low byte for testing # 300
aHi:	dc	0b00000001 	# replace 0 by your choice of high byte for testing
bLo:	dc	0b11100100 	# replace 0 by your choice of low byte for testing # 1508
bHi:	dc	0b00000101 	# replace 0 by your choice of high byte for testing
ENDINPUTS>

resLo:	ds	1
resHi:  ds  1		# two bytes reserved for the result
end


