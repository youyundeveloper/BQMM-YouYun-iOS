//
//  YYBaseViewController.m
//  YYEmotionDemo
//
//  Created by Frederic on 16/9/8.
//  Copyright © 2016年 17YouYun. All rights reserved.
//

#import "YYBaseViewController.h"

#import "SVProgressHUD.h"

@interface YYBaseViewController ()

@end

@implementation YYBaseViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    self.view.backgroundColor = [UIColor whiteColor];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark - HUD

- (void)setDefaultHUD {
    [SVProgressHUD setDefaultStyle:SVProgressHUDStyleDark];
    [SVProgressHUD setDefaultMaskType:SVProgressHUDMaskTypeClear];
    [SVProgressHUD setDefaultAnimationType:SVProgressHUDAnimationTypeFlat];
}

- (BOOL)hudIsVisible {
    return [SVProgressHUD isVisible];
}

- (void)showHUD {
    dispatch_async(dispatch_get_main_queue(), ^{
        [self setDefaultHUD];
        [SVProgressHUD show];
    });
}

- (void)showHUDWithStatus:(NSString *)status {
    dispatch_async(dispatch_get_main_queue(), ^{
        [SVProgressHUD showWithStatus:status];
    });
}

- (void)showHUDProgress:(float)progress status:(NSString*)status {
    dispatch_async(dispatch_get_main_queue(), ^{
        [SVProgressHUD showProgress:progress status:status];
    });
}

- (void)showHUDInfoWithStatus:(NSString*)status {
    dispatch_async(dispatch_get_main_queue(), ^{
        [SVProgressHUD showInfoWithStatus:status];
    });
}

- (void)showHUDSuccessWithStatus:(NSString*)status {
    dispatch_async(dispatch_get_main_queue(), ^{
        [SVProgressHUD showSuccessWithStatus:status];
    });
}

- (void)showHUDErrorWithStatus:(NSString*)status {
    dispatch_async(dispatch_get_main_queue(), ^{
        [SVProgressHUD showErrorWithStatus:status];
    });
}

- (void)dismissHUD {
    dispatch_async(dispatch_get_main_queue(), ^{
        [SVProgressHUD dismiss];
    });
}

- (void)dismissHUDWithDelay:(NSTimeInterval)delay {
    dispatch_async(dispatch_get_main_queue(), ^{
        [SVProgressHUD dismissWithDelay:delay];
    });
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
