fex: 
	 $(info 🔨   We're building! Hold on...)
	 mkdir -p bin; gcc -std=c99 -pedantic -o bin/fex src/*.c

clean:
	 $(info 🧹   Let's clean everything up...)
	 rm -f bin/*

