
%%

int                     { printf("INT\n"); }
float                   { printf("FLOAT\n"); }
return                  { printf("RETURN\n"); }

[a-zA-Z]+[a-zA-Z0-9_]*  { printf("TOKEN\n"); }
"("                       { printf("LEFT(\n"); }

%%
