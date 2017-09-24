__global__ bitonic()
{
	const auto tIdx = threadIdx.x;
	const int array_size = 1024;
	__share__ int array[];

	for(int stage = 1; stage <= 10; stage++)
	{
		const int seq = (int)powf(2f,(float)stage);
		const thd_in_seq = seq/2;
		const int seqIdx = tIdx / thd_in_seq;
		const int idx_in_seq = tIdx % thd_in_seq;
		bool orient = seqIdx & 0x1;// 0:desencding
		const int base = seqIdx * seq;
		for(int step = 1; step <= stage; step++)
		{
			const int step_size = seq / pwdf(2f, (float)(step-1));
			const int thd_in_step = thd_in_seq / pwdf(2f,(float)(step-1));
			const int groupIdx = idx_in_seq / thd_in_step;
			cosnt int idx_in_step = idx_in_seq % thd_in_step;
			const int distance_swap = seq / (int)powf(2f,(float)step);
			const after_base = base + groupIdx * step_size + idx_in_step;
			
			swap(array[after_base], array[after_base+distance_swap])

		}


	}




}
