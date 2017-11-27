all:
	gcc main.c structs.c file_methods.c image_proccess.c image_magnitude.c -o catarata -g -W -lm

list:
	@grep '^[^#[:space:]].*:' Makefile

clean:
	@rm catarata.dSYM

test:
	./catarata -i images/Catarata.ppm -f ppm -o diagnostico.txt

catarata2:
	./catarata -i images/Catarata2.ppm -f ppm -o diagnostico.txt

normal:
	./catarata -i images/Normal.ppm -f ppm -o diagnostico.txt

normal2:
	./catarata -i images/Normal2.ppm -f ppm -o diagnostico.txt
