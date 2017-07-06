package be.uantwerpen.ansymo.semanticadaptation.cg.canonical.graph;

import java.util.Iterator;

import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.InnerFMU;

public class FMUGraph extends DirectedGraph<InnerFMU> {

    @Override
    public String toString(){
    	String result = "";
    	Iterator<InnerFMU> iterator = this.iterator();
    	while(iterator.hasNext()){
    		InnerFMU srcNode = iterator.next();
    		for (InnerFMU tgtNode : this.edgesFrom(srcNode)) {
    			result += srcNode.getName() + "-->" + tgtNode.getName() + '\n';    			
			}
    	}
		return result;
    }
}
