debug: ep1d.exe

build: ep1.exe

run: ep1.exe
	./ep1.exe teste.txt saida.txt

rund: ep1.exe
	./ep1d.exe teste.txt saida.txt

ep1d.exe: EP1.c
	gcc EP1.c driverEP1.c -o ep1d.exe -g

ep1.exe: EP1.c
	gcc EP1.c driverEP1.c -o ep1.exe

clean:
	del *.exe