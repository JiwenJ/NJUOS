#include "lib.h"
#include "types.h"
#define N 5
int uEntry(void) {
// 	// 测试scanf	
// 	int dec = 0;
// 	int hex = 0;
// 	char str[6];
// 	char cha = 0;
int ret = 0;
	
// 	while(1){
// 		printf("Input:\" Test %%c Test %%6s %%d %%x\"\n");
// 		ret = scanf(" Test %c Test %6s %d %x", &cha, str, &dec, &hex);
// 		printf("Ret: %d; %c, %s, %d, %x.\n", ret, cha, str, dec, hex);
// 		if (ret == 4)
// 			break;
// 	}
// 	//exit(0);
// 	return 0;
// }

	
	// 测试信号量
	int i = 4;
	sem_t sem;
	printf("Father Process: Semaphore Initializing.\n");
	ret = sem_init(&sem, 0);
	if (ret == -1) {
		printf("Father Process: Semaphore Initializing Failed.\n");
		exit(1);
	}

	ret = fork();
	if (ret == 0) {
		while( i != 0) {
			i --;
			printf("Child Process: Semaphore Waiting.\n");
			sem_wait(&sem);
			printf("Child Process: In Critical Area.\n");
		}
		printf("Child Process: Semaphore Destroying.\n");
		sem_destroy(&sem);
		exit();
	}
	else if (ret != -1) {
		while( i != 0) {
			i --;
			printf("Father Process: Sleeping.\n");
			sleep(128);
			printf("Father Process: Semaphore Posting.\n");
			sem_post(&sem);
		}
		printf("Father Process: Semaphore Destroying.\n");
		sem_destroy(&sem);
		//exit(); //we can not exit here for following philosopher design
	}
	exit(0);
	return 0;
}
// 	// For lab4.3
	// TODO: You need to design and test the philosopher problem.
	// Note that you can create your own functions.
	// Requirements are demonstrated in the guide.
	
	// //哲学家
	// //outline           with maximum 4 philos can request for forks,  5 philos can start at same time
// 	int uEntry(void) {
// 	sem_t mutex; 
// 	sem_t max_request;
// 	pid_t pilo_id = 0;
// 	//pid_t pilo_id_arr[4];
// 	if(  sem_init(&mutex,1) == -1)
// 	{
// 		printf("mutex init failed\n");
// 		exit(0);
// 	}
// 	if( sem_init(&max_request,4) == -1)
// 	{
// 		printf("max_request sem init failed\n");
// 		exit(0);
// 	}
// 	for(int i = 0; i <4; i++)
// 	{
// 		pilo_id = fork();
// 		if(pilo_id == 0)break;
// 		else continue;
// 	}
// 	if(pilo_id != 0)//main process
// 	{
// 		//think
// 		printf("pilosopher %d is thinking\n",getpid() );
// 		sleep(1280);
// 		sem_wait(&max_request);
// 		//eat
// 		printf("pilosopher %d is eating\n",getpid() );
// 		sleep(1280);
// 		sem_post(&max_request);
// 	}
// 	else if(pilo_id == 0)//other 4 processes
// 	{
// 		//think
// 		printf("pilosopher %d is thinking\n",getpid() );
// 		sleep(1280);
// 		sem_wait(&max_request);
// 		//eat
// 		printf("pilosopher %d is eating\n",getpid() );
// 		sleep(1280);
// 		sem_post(&max_request);
// 	}
// 	//生产者消费者问题
// 	//读者写者问题
// 	exit(0);
// 	return 0;
// }
