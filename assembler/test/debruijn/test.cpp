#define K 27
#define R 100
#define I 220
#define DE_BRUIJN_DATA_FOLDER "./data/debruijn/"
#define INPUT QUAKE_CROPPED_10_5

/////////////////
//for read generator
//#define SUBSTR_LENGTH 10000
//#define COVERAGE 30
//#define R 35
/////////////////


#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "debruijn_graph_test.hpp"

#include "edge_graph_test.hpp"
#include "edge_graph_tool.hpp"
#include "visualization_utils.hpp"
#include "ireadstream.hpp"

#include <tr1/tuple>

void RunTestSuites() {
	cute::suite s;
	//TODO add your test here
//	s += de_bruijn::DeBruijnGraphSuite();
	s += edge_graph::EdgeGraphSuite();
	cute::ide_listener lis;
	cute::makeRunner(lis)(s, "De Bruijn Project Test Suites");
}

void RunEdgeGraphTool() {
	typedef StrobeReader<2, Read, ireadstream> ReadStream;
	typedef PairedReader<ireadstream> PairedStream;
	typedef RCReaderWrapper<PairedStream> RCStream;

	//	const tr1::tuple<string, string, int> input = ;
	const string reads[2] = {tr1::get<0>(INPUT), tr1::get<1>(INPUT)};
	ReadStream reader(reads);
	PairedStream pairStream(reader, tr1::get<2>(INPUT));
	RCStream rcStream(pairStream);

	ireadstream genome_stream(ECOLI_FILE);
	Read genome;
	genome_stream >> genome;
	edge_graph::EdgeGraphTool(rcStream,  genome.getSequenceString().substr(0, tr1::get<2>(INPUT)));
	reader.close();
	genome_stream.close();
}

int main() {
//	RunTestSuites();
	RunEdgeGraphTool();
	return 0;
}
