all:
	gcc main.c file_methods.c image_proccess.c image_magnitude.c -o catarata -g -W

catarata:
	./catarata -i Catarata.ppm -f ppm -o diagnostico.txt

catarata2:
	./catarata -i Catarata2.ppm -f ppm -o diagnostico.txt

normal:
	./catarata -i Normal.ppm -f ppm -o diagnostico.txt

normal2:
	./catarata -i Normal2.ppm -f ppm -o diagnostico.txt
