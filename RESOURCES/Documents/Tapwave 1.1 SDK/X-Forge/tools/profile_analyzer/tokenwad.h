#ifndef TOKENWAD_INCLUDED
#define TOKENWAD_INCLUDED
#define TOKENWAD_DEBUGMODE

// Simple string tokenizer class
// Jari Komppa 2001
class tokenwad {
public:
  tokenwad() { t=NULL; count=0; }
  ~tokenwad() { for (int i=0;i<count;i++) delete[] t[i]; delete[] t; }
  void tokenize(const char * buf, const char * separators) {
    // if reusing this tokenizer, clean up old mess:
    if (t!=NULL) {
      for (int i=0;i<count;i++) {
        delete[] t[i]; 
      }
      delete[] t;
      count=0;
      t=NULL;
    }
    if (buf==NULL) return;
    int sepcount=0;
    while (separators[sepcount]!=0) sepcount++;
    // pass 1: count tokens
    count=1;
    int i=0;
    while (buf[i]!=0) {      
      for (int j=0;j<sepcount;j++)
        if (buf[i]==separators[j]) 
          count++;
      i++;
    }
    int * offsets=new int[count+1];
    int * lengths=new int[count+1];
    count=0;
    offsets[0]=0;
    i=0;
    // pass 2: count token sizes and offsets
    while (buf[i]!=0) {      
      for (int j=0;j<sepcount;j++)
        if (buf[i]==separators[j]) 
          offsets[++count]=i+1;
      i++;
    }
    offsets[++count]=i+1;
    // pass 3: trim
    
    for (i=0;i<count;i++) {
      // ltrim
      //while (buf[offsets[i]]==32 || buf[offsets[i]]==9) offsets[i]++;
      // rtrim
      lengths[i]=offsets[i+1]-(offsets[i]+1);
      //while (lengths[i]>0 && (buf[offsets[i]+lengths[i]-1]==32 || buf[offsets[i]+lengths[i]-1]==9)) lengths[i]--;
    }
    
    // pass 4: allocate
    t=new char*[count];
    for (i=0;i<count;i++) {
      t[i]=new char[lengths[i]+1];
      t[i][lengths[i]]=0;
    }

    // pass 5: copy tokens
    for (i=0;i<count;i++)
      for (int j=offsets[i],c=0;j<offsets[i]+lengths[i];j++,c++)
        t[i][c]=buf[j];
    delete[] offsets;
    delete[] lengths;
  }
  void tokenize(const char * buf) {
    tokenize(buf,"=,");
  }
  int tokenequals(int tokenidx, const char * compareto) {
    const char * t1=token(tokenidx), * t2=compareto;
    while (*t1!=0 && *t2!=0 && *t1==*t2) { t1++; t2++; }
    if (*t1==*t2) return 1;
    return 0;
  }
  int tokenequalsnocase(int tokenidx, const char * compareto) {
    const char * t1=token(tokenidx), * t2=compareto;
    while (*t1!=0 && *t2!=0 && upcase(*t1)==upcase(*t2)) { t1++; t2++; }
    if (*t1==*t2) return 1;
    return 0;
  }
  int tokens() { return count; }
  const char * token(int idx) { return (const char*)t[idx]; }
  char * tokendup(int idx) { 
    int l=0;
    const char * s=t[idx];
    while (s[l]!=0) l++;
    char * dup=new char[l+1];
    dup[l]='\0';
    memcpy(dup,s,l);
    return dup;
  }

#ifdef TOKENWAD_DEBUGMODE
  // Dump contents; buffer had better be big enough =)
  void dumpcontents(char * buf) {
    sprintf(buf,"TokenWad dump - %d tokens:\r\n",count);
    int ofs=strlen(buf);
    for (int i=0;i<count;i++) {
      buf[ofs++]='"';
      int l=strlen(t[i]);
      memcpy(buf+ofs,t[i],l);
      ofs+=l;
      buf[ofs++]='"';
      buf[ofs++]='\r';
      buf[ofs++]='\n';
    }
    buf[ofs++]='\0';
  }
#endif

private:
  // Token strings
  char ** t;  
  // Number of token strings
  int count;
  // upcase
  char upcase(char i) {
    if (i>='a' && i<='z') return i-('a'-'A');
    return i;
  }
};
#endif // TOKENWAD_INCLUDED