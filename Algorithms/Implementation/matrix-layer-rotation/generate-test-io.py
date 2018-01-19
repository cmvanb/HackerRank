# generate-test-io
# This program generates a test input file for the matrix layer rotation algorithm.
import argparse

parser = argparse.ArgumentParser(description='')
parser.add_argument('filename')
parser.add_argument('rows', type=int)
parser.add_argument('columns', type=int)
parser.add_argument('rotations', type=int)
args = parser.parse_args()

filename = args.filename + '.txt'
file = open(filename, 'w')
file.write('{0} {1} {2}'.format(args.rows, args.columns, args.rotations))
file.write('\n')
elements = args.rows * args.columns

for x in range(0, elements):
    file.write(str(x + 1))
    if (x + 1) % args.columns == 0:
        file.write('\n')
    else:
        file.write(' ')
file.close()

