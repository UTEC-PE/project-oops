void imprimirMatriz(vector<vector<int>> matrix){
	for(auto i:matrix){
		for(auto j:i){
			if(j<inf-200)
				cout<<j<<"\t";
			else
				cout<<"inf"<<"\t";
		}
		cout<<endl;
	}
}

void imprimirVector(vector<int> vec){
        for(auto i:vec){
                if(i<inf-200)
                        cout<<i<<"\t";
                else
                        cout<<"inf"<<"\t";
        }
}