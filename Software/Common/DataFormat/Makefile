CXXFLAGS = -std=c++11

runtest: test
	./test

test: DifferenceEcgCompressor.o FlatEcgPredictor.o BitFifo.o StreamSerializer.o helpers.o PacketReader.o

clean:
	rm *.o test
