import sys

def borrar(s):
	with open(s, 'r') as f:
		ff = f.readlines()
		if ("#" in ff[0]):
			ff = ff[1:]

	with open(s, 'w') as f2:
		f2.writelines(ff)

if __name__ == "__main__":
	s = sys.argv[1]
	borrar(s)
