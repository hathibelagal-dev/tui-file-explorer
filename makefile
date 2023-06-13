fex: 
	 $(info 🔨   We're building to minimize size! Hold on...)
	 mkdir -p bin
	 gcc -std=c99 -pedantic -Wstrict-prototypes -Os src/*.c -o bin/fex -lmagic

fast: 
	 $(info 🔨   We're building to maximize performance! Hold on...)
	 mkdir -p bin
	 gcc -std=c99 -pedantic -Wstrict-prototypes -O3 src/*.c -o bin/fex -lmagic	 

clean:
	 $(info 🧹   Let's clean everything up...)
	 rm -f bin/*

