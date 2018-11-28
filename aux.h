void imprimirMatriz(vector<vector<int>> matrix){
        	for(auto i:matrix){
        		for(auto j:i){
        			if(j!=inf)
        				cout<<j<<"\t";
        			else
        				cout<<"inf"<<"\t";
        		}
        		cout<<endl;
        	}
        }