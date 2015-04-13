void makeGameScreens(char* screenChunk1 ,char* screenChunk2)
{
	long readfile;
	long *fastCopyptSrc = screenChunk1;
	long *fastCopyptDst = screenChunk2;
	int  handle;
	long i;
		
	readfile = Fopen("grass.pi1",0);
	
	handle = (readfile &= 0x0000FFFF); /*handle is in lower word */
	
	Fseek(34,handle,0); /*align to data offset in degas file */
	 
	readfile = Fread(handle,FILE_SIZE,fastCopyptSrc); /*load data to mem */
	
	if(readfile != 0){
		
		readfile = SCREEN_SIZE >> 3;
	
	for(i = 0 ;i < readfile;i++)
	{
	
		*(fastCopyptDst++) = *(fastCopyptSrc++);
		*(fastCopyptDst++) = *(fastCopyptSrc++);
		*(fastCopyptDst++) = *(fastCopyptSrc++);
		*(fastCopyptDst++) = *(fastCopyptSrc++);
		*(fastCopyptDst++) = *(fastCopyptSrc++);
		*(fastCopyptDst++) = *(fastCopyptSrc++);
		*(fastCopyptDst++) = *(fastCopyptSrc++);
		*(fastCopyptDst++) = *(fastCopyptSrc++);
	
	}	
	
	
	}
	
	
	else
	{
	
	Cconws("Error in file reading " );
	
	}
	
	Fclose(handle);
	

}