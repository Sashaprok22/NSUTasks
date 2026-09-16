asect  0x00


# =================================
# LEAVE THIS PART OF THE FILE ALONE
# Do not change the next two instructions: they must be the last two
# instructions executed by your program.
ldi r0, a   
halt         # Brings execution to a halt

# =================================
# DATA GOES BELOW
# Just add here the data definitions as instructed.
# (different values, starting with address a)
# ---------------------------------------------------------------------
INPUTS>
a: dc 13, 0x45, 0b11001101, "A" 
ENDINPUTS>

end



