CXXFLAGS = -std=c++11

runtest: test circularBufferTest
	./test
	./circularBufferTest

test: DifferenceEcgCompressor.o FlatEcgPredictor.o BitFifo.o helpers.o PacketReader.o Packetizer.o

clean:
	rm *.o test
