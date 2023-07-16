import 'package:flutter/material.dart';
import 'screeen/screen_home.dart';

void main() {
  runApp(MainApp());
}

class MainApp extends StatelessWidget {
  const MainApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'My Quiz App',
      home: HomeScreen(),
    );
  }
}
