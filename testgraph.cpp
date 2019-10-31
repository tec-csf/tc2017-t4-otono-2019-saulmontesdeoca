/*
Código tomado como referencia de https://github.com/alberto911/exportGraphs/commits?author=alberto911
*/

#include <iostream>
#include <fstream>
#include "Snap.h"
#include <ctime>

typedef PNGraph MyGraphType;

void GraphML(MyGraphType g) {
	std::ofstream file ("fb.graphml");
	if (file.is_open()) {
		file << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
		file << "<graphml xmlns=\"http://graphml.graphdrawing.org/xmlns\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:schemaLocation=\"http://graphml.graphdrawing.org/xmlns http://graphml.graphdrawing.org/xmlns/1.0/graphml.xsd\">\n";
		file << "<graph id=\"G\" edgedefault=\"directed\">\n";

		for (MyGraphType::TObj::TNodeI NI = g->BegNI(); NI < g->EndNI(); NI++)
			file << "<node id=\"" << NI.GetId() << "\"/>\n";

		int i = 1;
		for (MyGraphType::TObj::TEdgeI EI = g->BegEI(); EI < g->EndEI(); EI++, ++i)
			file << "<edge id=\"e" << i << "\" source=\"" << EI.GetSrcNId() << "\" target=\"" << EI.GetDstNId() << "\"/>\n";

		file << "</graph>\n";
		file << "</graphml>\n";
		file.close();
	}
}

void GEXF(MyGraphType g) {
	std::ofstream file ("fb.gexf");
	if (file.is_open()) {
		file << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
		file << "<gexf xmlns=\"http://www.gexf.net/1.2draft\" version=\"1.2\">\n";
		file << "<graph mode=\"static\" defaultedgetype=\"directed\">\n";
		
		file << "<nodes>\n";
		for (MyGraphType::TObj::TNodeI NI = g->BegNI(); NI < g->EndNI(); NI++)
			file << "<node id=\"" << NI.GetId() << "\" />\n";
		file << "</nodes>\n";

		file << "<edges>\n";
		int i = 1;
		for (MyGraphType::TObj::TEdgeI EI = g->BegEI(); EI < g->EndEI(); EI++, ++i)
			file << "<edge id=\"" << i << "\" source=\"" << EI.GetSrcNId() << "\" target=\"" << EI.GetDstNId() << "\" />\n";
		file << "</edges>\n";

		file << "</graph>\n";
		file << "</gexf>\n";
		file.close();
	}
}

void GDF(MyGraphType g) {
	std::ofstream file ("fb.gdf");
	if (file.is_open()) {
		file << "nodedef>id VARCHAR\n";
		for (MyGraphType::TObj::TNodeI NI = g->BegNI(); NI < g->EndNI(); NI++)
			file << NI.GetId() << "\n";

		file << "edgedef>source VARCHAR, destination VARCHAR\n"; 
		for (MyGraphType::TObj::TEdgeI EI = g->BegEI(); EI < g->EndEI(); EI++)
			file << EI.GetSrcNId() << ", " << EI.GetDstNId() << "\n";

		file.close();
	}
}

void JSON(MyGraphType g) {
	std::ofstream file ("fb.json");
	if (file.is_open()) {
		file << "{ \"graph\": {\n";
		file << "\"nodes\": [\n";
		for (MyGraphType::TObj::TNodeI NI = g->BegNI(); NI < g->EndNI(); ) {
			file << "{ \"id\": \"" << NI.GetId() << "\" }";
			if (NI++ == g->EndNI())
				file << " ],\n";
			else
				file << ",\n";
		}

		file << "\"edges\": [\n";
		for (MyGraphType::TObj::TEdgeI EI = g->BegEI(); EI < g->EndEI(); ) {
			file << "{ \"source\": \"" << EI.GetSrcNId() << "\", \"target\": \"" << EI.GetDstNId() << "\" }";
			if (EI++ == g->EndEI())
				file << " ]\n";
			else
				file << ",\n";
		}
		file << "} }";

		file.close();
	}
}

int main() {
	MyGraphType dg = TSnap::LoadEdgeList<MyGraphType>("fb.txt",0,1);
	
	GraphML(dg);

	GEXF(dg);

	GDF(dg);

	JSON(dg);
	return 0;
}