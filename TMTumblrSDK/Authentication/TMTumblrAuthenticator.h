//
//  TMTumblrAuthenticator.h
//  TumblrAuthentication
//
//  Created by Bryan Irace on 11/19/12.
//  Copyright (c) 2012 Tumblr. All rights reserved.
//

#if __IPHONE_OS_VERSION_MIN_REQUIRED
@class UIWebView;
#define TMWebView UIWebView
#else
@class WebView;
#define TMWebView WebView
#endif

typedef void (^TMAuthenticationCallback)(NSString *, NSString *, NSError *);

/**
 Provides three-legged OAuth and xAuth implementations for authenticating with the Tumblr API.
 */
@interface TMTumblrAuthenticator : NSObject

/// OAuth consumer key. Must be set prior to authenticating or making any API requests.
@property (nonatomic, copy) NSString *OAuthConsumerKey;

/// OAuth consumer key. Must be set prior to authenticating or making any API requests.
@property (nonatomic, copy) NSString *OAuthConsumerSecret;

+ (TMTumblrAuthenticator *)sharedInstance;

/**
 Authenticate via three-legged OAuth.
 
 Your `TMTumblrAuthenticator` instance's `handleOpenURL:` method must also be called from your `UIApplicationDelegate`'s
 `application:openURL:sourceApplication:annotation:` method in order to receive the tokens.
 
 @param URLScheme a URL scheme that your application can handle requests to.
 */
- (void)authenticate:(NSString *)URLScheme callback:(TMAuthenticationCallback)callback;

- (void)postTokenRequest:(void(^)(NSURL *url, NSString *oauthToken))successBlock oauthCallBack:(NSString *)oauthCallBack errorBlock:(void(^)(NSError *error))errorBlock;
- (void)postAccessTokenRequestWithPIN:(NSString *)pin
                           oauthToken:(NSString *)oauthToken
                         successBlock:(void(^)(NSString *oauthToken, NSString *oauthTokenSecret, NSString *userID, NSString *screenName))successBlock
                           errorBlock:(void(^)(NSError *error))errorBlock;
/**
 Authenticate via three-legged OAuth. This should be called from your `UIApplicationDelegate`'s
 `application:openURL:sourceApplication:annotation:` method in order to receive the tokens.
 
 This method is the last part of the authentication flow started by calling `authenticate:callback:`
 */
- (BOOL)handleOpenURL:(NSURL *)url;

/**
 Authenticate via xAuth.
 
 Please note that xAuth access [must be specifically requested](http://www.tumblr.com/oauth/apps) for your application.
 */
- (void)xAuth:(NSString *)emailAddress password:(NSString *)password callback:(TMAuthenticationCallback)callback;

@end