#include<stdio.h>
#include<string.h>

/* REturn the clock speed of the system CPU in MHz, as reported by /proc/cpuinfo.
 * On a multiprocessor system return the speed of the first CPU else error.
 */

float get_cpu_clock_speed(){
    FILE *fp;
    char buffer[100480];
    size_t bytes_read;
    char* match;
    float clock_speed;

    //read the entire contents of the /proc/cpuinfo into the buffer
    fp=fopen("/proc/cpuinfo","r");
    if(fp==NULL)
        printf("Error opening file\n");
    else    printf("file opened\n");
    bytes_read=fread(buffer,1,sizeof(buffer),fp);
    fclose(fp);

    printf("size of buffer: %d\n",sizeof(bytes_read));
    //bail if read failed or buffer isn't big enough.
    if(bytes_read==0||bytes_read==sizeof(buffer))
        return 0;

    //null terminate the text
    buffer[bytes_read]='\0';

    //locate the line that starts with cpu MHz
    match=strstr(buffer,"cpu MHz");
    if(match==NULL)
        return -1;
    //parse the line to extract the clock speed
    sscanf(match,"cpu MHz : %f",&clock_speed);
    return clock_speed;
}

int main(){
    printf("CPU clock speed: %4.0f MHz\n",get_cpu_clock_speed());
    return 0;
}
