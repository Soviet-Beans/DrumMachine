void setup()
{
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
}

void printLine()
{
  Serial.println();
}

template <typename T, typename... Types>
void printLine(T first, Types... other)
{
  Serial.print(first);
  printLine(other...);
}

void loop()
{
  int val1 = analogRead(A0);
  int val2 = analogRead(A1);
  printLine(val1, ":", val2);
  delay(1000);
}