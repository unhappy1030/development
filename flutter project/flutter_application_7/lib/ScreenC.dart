import 'package:flutter/material.dart';

class ScreenC extends StatelessWidget {
  const ScreenC({super.key});

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('ScreenC'),
        backgroundColor: Colors.redAccent,
      ),
      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            Text(
              'ScreenC',
              style: TextStyle(
                fontSize: 45,
                fontWeight: FontWeight.w800,
                color: Colors.redAccent,
              ),
            ),
          ],
        ),
      ),
    );
  }
}
