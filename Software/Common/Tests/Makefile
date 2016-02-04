CXXFLAGS = -std=c++11 -I../SignalConditioning -I../DataFormat -I../

runtest: testSignalConditioning testDataFormat
	./testSignalConditioning
	./testDataFormat
	echo "All tests passed."

testDataFormat: ../DataFormat/DifferenceEcgCompressor.o ../DataFormat/FlatEcgPredictor.o ../DataFormat/BitFifo.o ../DataFormat/helpers.o ../DataFormat/PacketReader.o ../DataFormat/Packetizer.o


clean:
	rm *.o testSignalConditioning
