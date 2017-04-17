#!/boot/home/config/bin/python

# Bidea v1.0 (c) 2000 Patrick H. Mullins
# 01/25/2000 8:29 PM
# An Idea frontend written in standard Python for BeOS x86 4.5.2

import os
os.system("clear")
print "BIdea Commandline Interface v 1.0"
print "by Patrick H. Mullins, (c) 2000"
print "==========================================================="
print "Note: You must know what type of file is being decrypted:"
print "i.e. .jpg, .zip and so on.  Also, this version has no error"
print "checking."
print ""
print "1  Encrypt File"
print "2  Decrypt File"
choice = input("> ")
if choice == 1:
   infile = raw_input("What file do you want to ecrypt: ")
   outfile = raw_input("Please type in a name for the ecrypted file: ")
   password = raw_input("Enter the password: ")
   os.system("idea -ek %s %s %s" % (password, infile, outfile))
   os.system("clear")
   print "All done."
else:
   infile = raw_input("What file do you want to decrypt: ")
   outfile = raw_input("Please type in a name for the decrypted file: ")
   password = raw_input("Enter the password: ")
   os.system("idea -dk %s %s %s" % (password, infile, outfile))
   os.system("clear")
   print "All done."
