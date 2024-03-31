#include "dragoness/dragonessFunctions.h"
#include "scripts/scriptAll.h"
int main() {
	if(dragonessInit() != 0) {
		return -1;
	}
	dragonessSetScriptExecFunction(mainScriptFunction);
	dragonessCreateScriptThread();
	dragonessRender();
	dragonessExit();
	return 0;
}
