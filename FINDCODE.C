main()
{
  char name[81],
       code[5];
  int i;

  printf("\n\nEnter BBS Name: ");
  gets(name);

  i = name[4];
  i += name[3];

  sprintf(code,"%d",i);

  printf("Code : %s",code);

}