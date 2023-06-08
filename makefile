fex: 
	 $(info 🔨   We're building! Hold on...)
	 gcc -o bin/fex src/*.c

clean:
	 $(info 🧹   Let's clean everything up...)
	 rm -f bin/*

