Program CJ;
(*
   BubbleSort
   ChoiceSort
   ShellSort, ShellSort_A102549e, ShellSort_pe, ShellSort_p2, ShellSort_p3x
   oQuickSort, QuickSort, cQuickSort
   TreeSort, xTreeSort, rTreeSort
   MatrixSort, HashSort
*)
Type
  SData = longint;

Const
  MaxNumber = 700000000;
  MaxSize = 64000*1;
  Sizes = round(ln(MaxSize/500)/ln(2));
  Size: longword = MaxSize;
  NP = 1; (* Number of passes *)

Var
  BaseArray, TempArray: array[1..MaxSize]of SData;
  Results: array [1..2, 1..4, 1..Sizes] of longint;
  Deviation: array[1..8, 1..4] of longint;
  i, j, k: byte;

{$L timer.o}
procedure init_timer; cdecl; external;
function get_timer: longint; cdecl; external;
{$LinkLib c}

Procedure FillArray(t: byte);
  var i: longint;
  begin
    randomize;
    case t of
      1:begin  (* desc *)
        BaseArray[1] := MaxNumber;
        for i := 2 to Size do
          BaseArray[i] := BaseArray[i - 1] - random(MaxNumber div Size) - 1
      end;
      2:begin (* asc *)
        BaseArray[1] := 1;
        for i := 2 to Size do
          BaseArray[i] := BaseArray[i - 1] + random(MaxNumber div Size) + 1
      end;
      3: (* random range between 1 and 12 *)
        for i := 1 to Size do
          BaseArray[i] := random(12) + 1;
      else (* random *)
        for i := 1 to Size do
          BaseArray[i] := random(MaxNumber) + 1
    end
  end;

Procedure Exchange(i1, i2: longint);
  var temp: SData;
  begin
    temp := BaseArray[i1];
    BaseArray[i1] := BaseArray[i2];
    BaseArray[i2] := temp
  end;

Procedure TestArray;
  var i: longint;
  begin
    for i := 1 to Size - 1 do
      if BaseArray[i] < BaseArray[i + 1] then begin
        writeln('Error!');
        halt
      end
  end;

Procedure BubbleSort;
  var
    i, UBound: longint;
    EndFlag: boolean;
  begin
    Ubound := Size-1;
    repeat
      EndFlag := true;
      for i := 1 to UBound do
        if BaseArray[i] < BaseArray[i + 1] then begin
          Exchange(i, i + 1);
          EndFlag := false
        end;
      dec(UBound)
    until EndFlag
  end;

Procedure ChoiceSort;
  var
    i, LBound, MaxIndex: longint;
    MaxElem: SData;
  begin
    LBound := 1;
    repeat
      MaxElem := BaseArray[LBound];
      for i := LBound + 1 to Size do
        if MaxElem < BaseArray[i] then begin
          MaxElem := BaseArray[i];
          MaxIndex := i
        end;
      if MaxElem <> BaseArray[LBound] then
        Exchange(LBound, MaxIndex);
      inc(LBound)
    until LBound = Size
  end;

Procedure ShellSort;
  var
    i, j, gap: longint;
  begin
    gap := Size div 2;
{    gap := round(exp(Trunc(ln(Size)/ln(2))*ln(2)));}
    while gap > 0 do begin
      for i := gap to Size - 1 do begin
        j := i - gap + 1;
        while BaseArray[j] < BaseArray[j + gap] do begin
          Exchange(j, j + gap);
          if j > gap then j := j - gap else break
        end
      end;
      gap := gap div 2
    end
  end;

Procedure ShellSort_A102549e;
  const
    x: array [0..16] of longint =
         (1919119, 706001, 259723, 95549, 35149, 12923, 4759, 1750, 701, 301, 132, 57, 23, 10, 4, 1, 0); (* A102549 *)
  var
    i, j, k, gap: longint;
  begin
    k := 0;
    while x[k] >= Size do inc(k);
    while x[k] > 0 do begin
      gap := x[k];
      for i := gap to Size - 1 do begin
        j := i - gap + 1;
        while BaseArray[j] < BaseArray[j + gap] do begin
          Exchange(j, j + gap);
          if j > gap then j := j - gap else break
        end
      end;
      inc(k)
    end
  end;

Procedure ShellSort_pe;
  const
    x: array [0..16] of longint = (* primes close to powers of e *)
         (3269011, 1202609, 442439, 162713, 59879, 22027, 8101, 2971, 1097, 401, 149, 53, 19, 7, 3, 1, 0);
  var
    i, j, k, gap: longint;
  begin
    k := 0;
    while x[k] >= Size do inc(k);
    while x[k] > 0 do begin
      gap := x[k];
      for i := gap to Size - 1 do begin
        j := i - gap + 1;
        while BaseArray[j] < BaseArray[j + gap] do begin
          Exchange(j, j + gap);
          if j > gap then j := j - gap else break
        end
      end;
      inc(k)
    end
  end;

Procedure ShellSort_p2;
  const
    x: array [0..21] of longint =
         (2097143, 1048573, 524287, 262147, 131071, 65537, 32771, 16381, 8191, 4093, 2041, 1023, 511, 253, 123, 61, 31, 11, 5, 
            2, 1, 0); (* primes close to powers of 2 *)
  var
    i, j, k, gap: longint;
  begin
    k := 0;
    while x[k] >= Size do inc(k);
    while x[k] > 0 do begin
      gap := x[k];
      for i := gap to Size - 1 do begin
        j := i - gap + 1;
        while BaseArray[j] < BaseArray[j + gap] do begin
          Exchange(j, j + gap);
          if j > gap then j := j - gap else break
        end
      end;
      inc(k)
    end
  end;

Procedure ShellSort_p3x;
  var j, i, v, h: longint;
  begin
     h := 1;
     while h < Size do
        h := 3*h + 1;
     h := (h - 1) div 3;
     while h <> 0 do begin
        i := h;
        j := i;
        v := BaseArray[i + 1];
        while i < Size do begin
           j := j - h;
           while (j >= 0) and (BaseArray[j + 1] < v) do begin
              BaseArray[j + h + 1] := BaseArray[j + 1];
              j := j - h
           end;
           BaseArray[j + h + 1] := v;
           inc(i);
           j := i;
           v := BaseArray[i + 1]
        end;
        h := (h - 1) div 3;
     end
  end;

Procedure oQuickSort(LBound, UBound: longint);
  var
    i, j: longint;
  begin
    i := LBound;
    j := UBound;
    repeat
      while i <> j do
        if BaseArray[i] >= BaseArray[j] then
          dec(j)
        else begin
          Exchange(i, j);
          break
        end;
      while i <> j do
        if BaseArray[i] >= BaseArray[j] then
          inc(i)
        else begin
          Exchange(i, j);
          break
        end
    until i = j;
    if i - 1 > LBound then oQuickSort(LBound, i - 1);
    if j + 1 < UBound then oQuickSort(j + 1, UBound)
  end;

Procedure QuickSort(LBound, UBound: longint);
  var
    i, j: longint;
    x: SData;
  begin
    i := LBound;
    j := UBound;
    x := BaseArray[(i + j) div 2];
    repeat
      while BaseArray[i] > x do inc(i);
      while x > BaseArray[j] do dec(j);
      if i <= j then begin
        Exchange(i, j);
        inc(i);
        dec(j)
      end
    until i > j;
    if LBound < j then QuickSort(LBound, j);
    if i < UBound then QuickSort(i, UBound)
  end;

type
   pword = ^SData;
   pfunc = function(a, b: pword): longint; cdecl;

function cmpnum(a, b: pword): longint; cdecl;
   begin
      {if a^ > b^ then
         cmpnum := -1
      else if a^ < b^ then
         cmpnum := 1
      else
         cmpnum := 0}
      cmpnum := b^ - a^;
   end;

procedure qsort(a: array of SData; q, s: longint; f: pfunc); cdecl; external;

procedure cQuickSort;
   begin
      qsort(basearray, size, 4, @cmpnum);
   end;

Procedure TreeSort;
  type
    tdirs = (left, right, up);
  var
    Tree: array[1..MaxSize] of record 
                                data: SData;
                                dirs: array [tdirs] of longint
                               end;
    i, j, k: longint;
    dir: tdirs;
  begin
    (* init *)
    for i := 1 to Size do 
      for dir := left to right do
        Tree[i].dirs[dir] := 0;
    (* building *)
    Tree[1].data := BaseArray[1];
    Tree[1].dirs[up] := 1;
    for i := 2 to Size do begin
      j := 1;
      repeat (* seek for a node to fill *)
        k := j;
        if Tree[j].data < BaseArray[i] then
          dir := left
        else
          dir := right;
        j := Tree[j].dirs[dir]
      until j = 0;
      Tree[i].data := BaseArray[i];
      Tree[i].dirs[up] := k;
      Tree[k].dirs[dir] := i
    end;
    (* output of sorted data -- a tree traversal *)
    dir := up; (* direction to a previous node *)
    i := 1; (* counter of unordered elements *)
    j := 1;    (* index of the root *)
    repeat
      case dir of
        up:begin
             while Tree[j].dirs[left] <> 0 do 
               j := Tree[j].dirs[left];
             BaseArray[i] := Tree[j].data;
             inc(i);
             if Tree[j].dirs[right] <> 0 then
               j := Tree[j].dirs[right]
             else begin
               if Tree[Tree[j].dirs[up]].dirs[left] = j then
                 dir := left
               else
                 dir := right;
               j := Tree[j].dirs[up]
             end
           end;
        left:begin
               BaseArray[i] := Tree[j].data;
               inc(i);
               if Tree[j].dirs[right] = 0 then begin
                 if Tree[Tree[j].dirs[up]].dirs[left] <> j then 
                   dir := right;
                 j := Tree[j].dirs[up]
               end else begin
                 j := Tree[j].dirs[right];
                 dir := up
               end
             end;
        right:begin
                if Tree[Tree[j].dirs[up]].dirs[left] = j then 
                  dir := left;
                j := Tree[j].dirs[up]
              end
      end
    until i > Size 
  end;

Procedure xTreeSort; {other direction of survey compensated by reverse index}
  type
    tdirs = (left, right, up);
  var
    Tree: array[1..MaxSize] of record 
                                 dirs: array [tdirs] of longint;
                                 data: SData
                              end; (* left, right, up, data *)
    i, j, k: longint;
    dir: tdirs;
  begin
    for i := 1 to Size do 
      for dir := left to right do
        Tree[i].dirs[dir] := 0;
    Tree[1].data := BaseArray[1];
    Tree[1].dirs[up] := 1;
    for i := 2 to Size do begin
      j := 1;
      repeat
        k := j;
        if Tree[j].data > BaseArray[i] then
          dir := left
        else 
          dir := right;
        j := Tree[j].dirs[dir]
      until j = 0;
      Tree[i].data := BaseArray[i];
      Tree[i].dirs[up] := k;
      Tree[k].dirs[dir] := i
    end;
    dir := right; (* current direction *)
    i := Size;    (* counter of unordered elements *)
    j := 1;       (* root's index *) 
    repeat
      if dir = right then
        while Tree[j].dirs[left] <> 0 do j := Tree[j].dirs[left]
      else begin
        while Tree[j].dirs[left] <> k do begin 
          k := j; 
          j := Tree[j].dirs[up] 
        end;
        dir := right;
      end;
      BaseArray[i] := Tree[j].data;
      dec(i);
      while Tree[j].dirs[dir] = 0 do 
        inc(dir);
      k := j;
      j := Tree[j].dirs[dir]
    until i = 0
  end;

Procedure rTreeSort; {don't use up direction, use recursion}
  type
    tdirs = (left, right);
    nodes = record 
                                data: SData;
                                dirs: array [tdirs] of longint
                               end;
  var
    Tree: array[1..MaxSize] of nodes;
    i, j, k: longint;
    dir: tdirs;
  procedure survey(inode: longint);
    begin
        if inode = 0 then exit;
        survey(Tree[inode].dirs[left]);
        basearray[i] := Tree[inode].data;
        inc(i);
        survey(Tree[inode].dirs[right]);
    end;

  begin
    for i := 1 to Size do 
      for dir := left to right do
        Tree[i].dirs[dir] := 0;
    Tree[1].data := BaseArray[1];
    for i := 2 to Size do begin
      j := 1;
      repeat        k := j;
        if Tree[j].data < BaseArray[i] then
          dir := left
        else
          dir := right;
        j := Tree[j].dirs[dir]
      until j = 0;
      Tree[i].data := BaseArray[i];
      Tree[k].dirs[dir] := i
    end;
    i := 1;
    survey(1);
  end;

var MinElem, MaxElem: SData;

procedure setMinMax; (* searches for max and min elements in BaseArray *)
   var i: longint;
   begin
      MinELem := BaseArray[1];
      MaxELem := BaseArray[1];
      for i := 2 to Size do begin
         if MaxElem < BaseArray[i] then
           MaxELem := BaseArray[i];
         if MinElem > BaseArray[i] then
           MinELem := BaseArray[i]
      end
   end;

Procedure MatrixSort;
  const
    factor = 1;
    limit = round(factor*MaxSize);
  var
    AuxArray: array [1..limit] of SData;
    i, j, l, UBound: longword;
    k, m: longint;
  begin
    setMinMax;
    if MaxElem = MinElem then exit; (* array is already sorted *)
    UBound := round(Size*factor);
    for i := 1 to UBound do
      AuxArray[i] := 0; (* zero elements are not occupied *)
    for i := 1 to Size do begin
      j := int64(BaseArray[i] - MinElem)*(UBound - 1) div (MaxElem - MinElem) 
             + 1;
      if AuxArray[j] = 0 then
        AuxArray[j] := BaseArray[i]
      else begin (* creation and search for a "window" *)
        if AuxArray[j] > BaseArray[i] then begin
          while j > 1 do
            if AuxArray[j - 1] > BaseArray[i] then
              dec(j)
            else
              break;
          m := -1
        end else begin
          while j < UBound do
            if (AuxArray[j + 1] < BaseArray[i]) 
                  and (AuxArray[j + 1] <> 0) then
              inc(j)
            else
              break;
          m := 1
        end;
        k := 0;
        repeat
          if (k + j > 0) and (k + j <= UBound) then
            if AuxArray[k + j] = 0 then 
               break;
          if k > 0 then k := -k else k := 1 - k
        until false;
        l := j + k;
        if k > 0 then k := 1 else k := -1;
        j := j + (m + k) div 2;
        while l <> j do begin
          AuxArray[l] := AuxArray[l - k];
          l := l - k
        end;
        AuxArray[j] := BaseArray[i]
      end
    end;
    j := 1;
    for i := UBound downto 1 do
      if AuxArray[i] <> 0 then begin
        BaseArray[j] := AuxArray[i];
        inc(j)
      end
  end;

procedure HashSort;
  type
     HashElement = record
        data: SData;
        next: longint;
     end;
  var 
     hashData: array[1..MaxSize]of HashElement;
     hashPtr: array[1..MaxSize] of longint;
     freePtr, i, j: longint;
  procedure Init;
     var i: longint;
     begin
        freePtr := 1;
        for i := 1 to size do
           hashPtr[i] := 0
     end;
  procedure AddElement(d: SData);
     label l1, l2;
     var 
        prevPtr, curPtr, j: longint;
     begin
        j := int64(d - MinElem)*(size - 1) div (MaxElem - MinElem) + 1;
        curPtr := hashPtr[j];
        if curptr = 0 then begin
           hashPtr[j] := freePtr;
           goto l1;
        end;
        prevPtr := 0;
        while curPtr <> 0 do begin
           if hashData[curptr].data < d then begin
              if prevPtr = 0 then begin
                 hashData[freePtr].next := hashPtr[j];
                 hashPtr[j] := freePtr;
              end else begin
                 hashData[prevPtr].next := freePtr;
                 hashData[freePtr].next := curPtr;
              end;
              goto l2; 
           end;
           prevPtr := curPtr;
           curPtr := hashData[curPtr].next
        end;
        hashData[prevPtr].next := freePtr;
l1:
        hashData[freePtr].next := 0;
l2:
        hashData[freePtr].data := d;
        inc(freePtr);
     end;

  begin
    setMinMax;
    if MaxElem = MinElem then exit;
    Init;
    for i := 1 to size do
       AddElement(basearray[i]);
    freePtr := 1;
    for i := size downto 1 do begin
       j := hashPtr[i];
       while j <> 0 do begin
          basearray[freePtr] := hashData[j].data;
          j := hashData[j].next;
          inc(freePtr);
       end
    end
  end;

function theoryfunc(e, t: byte): longint;
  begin
    case t of
      0: (* T(n) = n *)
        theoryfunc := (Results[e, j, i - 1] + 1) div 2;
      1: (* T(n) = n*log(n) *)
        theoryfunc := round(Results[e, j, i - 1]/(ln(2)/ln(Size) + 1)/2); 
      2: (* T(n) = n*log(n)*log(n) *)
        theoryfunc := round(Results[e, j, i - 1]/sqr(ln(2)/ln(Size) + 1)/2); 
      3: (* T(n) = n*n *) 
        theoryfunc := (Results[e, j, i - 1] + 2) div 4;
    end
  end;

begin
  for k := 1 to 2 do
    for i := 1 to Sizes do
      for j := 1 to 4 do
        Results[k, j, i] := 0;
  for k := 1 to NP do begin
    Size := MaxSize;
    for i := 1 to Sizes do begin
      for j := 1 to 4 do begin
        FillArray(j);
        TempArray := BaseArray;
        init_timer;
{        BubbleSort;}
{        ChoiceSort;}
{        ShellSort_p3x;}
{        ShellSort_p2;}
{        oQuickSort(1, Size);}
{        QuickSort(1, Size);}
{        cQuickSort1;}
{        TreeSort;}
        xTreeSort;
{        rTreeSort;}
{        MatrixSort;}
{        HashSort;}
        Results[1, j, i] :=  Results[1, j, i] + get_timer;
        TestArray;
        BaseArray := TempArray;
        init_timer;
{        BubbleSort;}
{        ChoiceSort;}
{        ShellSort;}
{        ShellSort_pe;}
{        ShellSort_A102549e;}
{        oQuickSort(1, Size);}
{        QuickSort(1, Size);}
{        cQuickSort;}
{        TreeSort;}
{        xTreeSort;}
        rTreeSort;
{        MatrixSort;}
{       HashSort;}
        Results[2, j, i] := Results[2, j, i] + get_timer;
        TestArray
      end;
      Size := Size div 2
    end
  end;
  for k := 1 to 2 do 
    for i := 1 to Sizes do
      for j := 1 to 4 do
        Results[k, j, i] := 
          (Results[k, j, i] + NP div 2) div NP;
  Size := MaxSize;
  for i := 1 to Sizes do begin
    write(Size: 7);
    for j := 1 to 4 do begin
      write(Results[1, j, i]/1000: 9: 2, '/', 
        Results[2, j, i]/1000: 8: 2)
    end;
    writeln;
    Size := Size shr 1
  end;
  for j := 1 to 4 do begin
    for k := 1 to 6 do
      Deviation[k, j] := 0;
    Size := MaxSize;
    for i := 2 to Sizes do begin
      Size := Size div 2;
      for k := 1 to 8 do
        Deviation[k, j] := Deviation[k, j] + 
          abs(theoryfunc(1 + (k + 1) mod 2, (k - 1) div 2) - 
            Results[1 + (k + 1) mod 2, j, i])*1000 div
              theoryfunc(1 + (k + 1) mod 2, (k - 1) div 2)
    end
  end;
  writeln
('   --------------------------------------------------------------------------');
  write('n': 7);
    for j := 1 to 4 do
      write(Deviation[1, j]: 9, '/', Deviation[2, j]: 8);
  writeln;
  write('n*ln(n)': 7);
    for j := 1 to 4 do
      write(Deviation[3, j]: 9, '/', Deviation[4, j]: 8);
  writeln;
  write('n*sl(n)': 7);
    for j := 1 to 4 do
      write(Deviation[5, j]: 9, '/', Deviation[6, j]: 8);
  writeln;
  write('n*n': 7);
    for j := 1 to 4 do
      write(Deviation[7, j]: 9, '/', Deviation[8, j]: 8);
  writeln
end.

