void mousePressed(){
  enter=0;
  now_enter=0;
  d=0;
  for(int i=0;i<30;i++){
    now[i]="";
  }
  background(0);
}
String insert(String original, String toInsert, int position){
  String p1 = original.substring(0,position);
  String p2 = original.substring(position);
  return p1 + toInsert + p2;
}
