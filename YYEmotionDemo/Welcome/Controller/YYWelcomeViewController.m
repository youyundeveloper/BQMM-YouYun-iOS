//
//  YYWelcomeViewController.m
//  YYEmotionDemo
//
//  Created by Frederic on 16/9/8.
//  Copyright © 2016年 17YouYun. All rights reserved.
//

#import "YYWelcomeViewController.h"

#import "YYConversationViewController.h"

#import "YYSDKManage.h"


@interface YYWelcomeViewController ()

@property (nonatomic, weak) UITextField *idTextFiled;

@property (nonatomic, weak) UIButton *startBtn;

@end



@implementation YYWelcomeViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    [self showHUD];
    __weak typeof(self) weakSelf = self;
    [[YYSDKManage sharedInstance]loginChatSDKCompletion:^(NSDictionary *userInfo, NSError *error) {
        if (error) {
            [weakSelf showHUDErrorWithStatus:error.localizedDescription];
        } else {
            // 授权成功
            NSString *userID = [NSString stringWithFormat:@"%@", userInfo[@"id"]];
            weakSelf.navigationItem.title = userID;
            [weakSelf showHUDSuccessWithStatus:nil];
            [weakSelf layputChatTextView];
        }
        
    }];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)layputChatTextView {
    
    UITextField *textFiled = [[UITextField alloc]initWithFrame:CGRectMake(15, 80, CGRectGetWidth(self.view.frame) - 30, 44)];
    textFiled.placeholder = @"请输入真实的对方ID开始";
    textFiled.font = [UIFont systemFontOfSize:17.0];
    textFiled.keyboardType = UIKeyboardTypeNumberPad;
    textFiled.clearButtonMode = UITextFieldViewModeWhileEditing;
    textFiled.alpha = 0.0;
    [self.view addSubview:textFiled];
    _idTextFiled = textFiled;
    
    UIButton *button = [UIButton buttonWithType:UIButtonTypeCustom];
    button.frame = CGRectMake(15, CGRectGetMaxY(_idTextFiled.frame) + 10, CGRectGetWidth(_idTextFiled.frame), 44);
    [button setTitle:@"开始" forState:UIControlStateNormal];
    button.backgroundColor = [UIColor purpleColor];
    [button addTarget:self action:@selector(startBtnAction) forControlEvents:UIControlEventTouchUpInside];
    button.alpha = 0.0;
    [self.view addSubview:button];
    _startBtn = button;
    
    [UIView animateWithDuration:0.75 animations:^{
        _idTextFiled.alpha = 1.0;
        _startBtn.alpha = 1.0;
    }];
    
}

- (void)startBtnAction {
    // 请传入用户ID，没有做校验
    if ([_idTextFiled.text isEqualToString:@""]) {
        return;
    }
    if (_idTextFiled.isFirstResponder) {
        [_idTextFiled resignFirstResponder];
    }
    YYConversationViewController *conVC = [[YYConversationViewController alloc]init];
    conVC.targetUserID = _idTextFiled.text;
    [self.navigationController pushViewController:conVC animated:YES];
}

@end