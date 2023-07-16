import 'package:flutter/material.dart';

class ScreenB extends StatelessWidget {
  const ScreenB({super.key});

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('ScreenB'),
        backgroundColor: Colors.teal,
      ),
      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            Text(
              'ScreenB',
              style: TextStyle(
                fontSize: 45,
                fontWeight: FontWeight.w800,
                color: Colors.teal,
              ),
            ),
          ],
        ),
      ),
    );
  }
}
