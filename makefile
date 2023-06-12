fex: 
	 $(info 🔨   We're building! Hold on...)
	 mkdir -p bin
	 gcc -std=c99 -pedantic -Wstrict-prototypes src/*.c -o bin/fex -lmagic

clean:
	 $(info 🧹   Let's clean everything up...)
	 rm -f bin/*

