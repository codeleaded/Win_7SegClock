//#define IMAGE_PNG_ONLY

#include "/home/codeleaded/System/Static/Library/WindowEngine1.0.h"

typedef struct DD7Segment {
	Sprite* digits;
	unsigned int count;
	unsigned int width;
	unsigned int height;
	char* path;
} DD7Segment;

void DD7Segment_Load(DD7Segment* s7,unsigned int width,unsigned int height){
	if(s7->width != width || s7->height != height){
		for(int i = 0;i<s7->count;i++){
			Sprite* sp = s7->digits + i;

			CStr name = CStr_Format("%s/%d.png",s7->path,i);
			Sprite_Free(sp);
			*sp = Sprite_Load(name);
			Sprite_Resize(sp,width,height);
			CStr_Free(&name);
		}
		s7->width = width;
		s7->height = height;
	}
}
DD7Segment DD7Segment_New(char* path,unsigned int width,unsigned int height){
	DD7Segment s7;
	s7.count = 10U;
	s7.width = 0U;
	s7.height = 0U;
	s7.path = CStr_Cpy(path);
	s7.digits = (Sprite*)malloc(sizeof(Sprite) * s7.count);
	memset(s7.digits,0,sizeof(Sprite) * s7.count);

	DD7Segment_Load(&s7,width,height);
	return s7;
}
void DD7Segment_Free(DD7Segment* s7){
	if(s7->digits){
		for(int i = 0;i<s7->count;i++){
			Sprite* sp = s7->digits + i;
			Sprite_Free(sp);
		}
		free(s7->digits);
	}
	CStr_Free(&s7->path);
}



DD7Segment s7;

void Setup(AlxWindow* w){
	s7 = DD7Segment_New("./assets",200,400);
}
void Update(AlxWindow* w){
	char buffer[128];
	memset(buffer,0,sizeof(buffer));
	Time_Str(buffer,Time_Nano());
	printf("\r%s",buffer);

	Time_t now = Time_Get(Time_Nano());
	
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