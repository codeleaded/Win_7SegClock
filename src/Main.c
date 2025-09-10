//#define IMAGE_PNG_ONLY

#include "/home/codeleaded/System/Static/Library/WindowEngine1.0.h"
#include "/home/codeleaded/System/Static/Library/DD7Segment.h"


DD7Segment s7;

void Setup(AlxWindow* w){
	s7 = DD7Segment_New("./assets",200,400);
}
void Update(AlxWindow* w){
	char buffer[128];
	memset(buffer,0,sizeof(buffer));
	Time_Str(buffer,Time_Real_Nano());
	printf("\r%s",buffer);

	Time_t now = Time_Get(Time_Real_Nano());
	
	Clear(BLACK);

	float px = 100.0f - 200.0f;
	float py = 100.0f;
	Sprite_RenderAlpha(WINDOW_STD_ARGS,s7.digits + (now.Hour / 10) % 10,px += 210.0f,py);
	Sprite_RenderAlpha(WINDOW_STD_ARGS,s7.digits + (now.Hour % 10),px += 210.0f,py);
	
	px += 100.0f;
	Sprite_RenderAlpha(WINDOW_STD_ARGS,s7.digits + (now.Min / 10) % 10,px += 210.0f,py);
	Sprite_RenderAlpha(WINDOW_STD_ARGS,s7.digits + (now.Min % 10),px += 210.0f,py);
	
	px += 100.0f;
	Sprite_RenderAlpha(WINDOW_STD_ARGS,s7.digits + (now.Sec / 10) % 10,px += 210.0f,py);
	Sprite_RenderAlpha(WINDOW_STD_ARGS,s7.digits + (now.Sec % 10),px += 210.0f,py);
}
void Delete(AlxWindow* w){
	DD7Segment_Free(&s7);
}

int main(){
    if(Create("7 Segment Display For Clock",1900,600,1,1,Setup,Update,Delete))
        Start();
    return 0;
}