<?php

setlocale(LC_ALL, 'en_US.UTF-8');
/**
 * Created by PhpStorm.
 * User: Peter
 * Date: 15/7/24
 * Time: 10:10
 */

class CampaignAction extends AdminCommonAction
{
    private $ModelName = 'CampaignAction';
    private $keys = array(
        //'id',
        'img',
        'url',
        'msg',
        'title',
        'type',
        'period_from',
        'period_to',
        );

    public function index()
    {
        // No datas, so just use below for test.
        $campaigns = array(
            array(
                'id'        => 1,
                'title'     => 'title',
                'msg'       => 'msg',
                'img'       => 'Public/Images/Home/logo.jpg',
                'type'      => '3',
                'period_from'   => '2015/07/10',
                'period_to'     => '2015/07/29',
            ),
        );
        $page = isset($_REQUEST['page']) && $_REQUEST['page'] >= 1 ? $_REQUEST['page'] : 1;
        $pageLimit = 10;
        $page_url = "?g=".GROUP_NAME."&m=".MODULE_NAME."&a=".ACTION_NAME."&page=[page]";

        $p=new Page($page,
            $pageLimit,
            1,
            $page_url,
            5,
            5);
        $pagelink=$p->showStyle(2);
        $this->assign('pagelink', $pagelink);
        $this->assign('campaigns', $campaigns);
        $this->assign('_hash_', buildFormToken());
        $this->assign('ur_href', '活动 &gt; 活动列表');
        $this->display();
    }


    /**
     * 删除
     *
     */
    public function del()
    {
        if(IS_AJAX){
            if(C('TOKEN_ON') && ! checkFormToken($_REQUEST)){
                die('hack attemp.');
            }
            $id = intval($_REQUEST['id']);
            if(true){
                $this->ajaxReturn('',buildFormToken(),1);
            }else{
                $this->ajaxReturn('','',0);
            }
        }
    }


    /**
     * 编辑
     *
     */
    public function edit()
    {
        $id = intval($_REQUEST['id']);
        if(IS_POST){
            if(C('TOKEN_ON') && ! checkFormToken($_POST)){
                die('hack attemp.');
            }
            /*
            for ($i = 0; $i < count($this->keys); $i++) {
                if ($_POST[$this->keys[$i]] == '')
                    die($this->keys[$i].'  数据有错');
            }
            unset($_POST['id']);
            $mModel = D($this->ModelName);
            if($mModel->editCampaign($id, $_POST)){
                $this->assign('jumpUrl', '?g='.GROUP_NAME.'&m='.MODULE_NAME);
                $this->success('编辑成功.');
            }else{
                $this->error('编辑失败');
            }
            */
            $this->assign('jumpUrl', '?g='.GROUP_NAME.'&m='.MODULE_NAME);
            $this->success('编辑成功.');
        }
        $mModel = D($this->ModelName);

        $campaign = array(
                'id'        => 1,
                'title'     => 'title',
                'msg'       => 'msg',
                'img'       => 'Public/Images/Home/logo.jpg',
                'type'      => '3',
                'period_from'   => '2015/07/10',
                'period_to'     => '2015/07/29',
        );
        $this->assign('campaign', $campaign);
        $this->assign('ur_href', ' &gt; 编辑商品');
        $this->assign('_hash_', buildFormToken());
        $this->display('post');
    }

    /**
     * 添加
     *
     */
    public function add()
    {
        if(IS_POST){
            if(C('TOKEN_ON') && ! checkFormToken($_POST)){
                die('hack attemp.');
            }   /* 檢測是否重複提交 */
            for ($i = 0; $i < count($this->keys); $i++) {
                if ($_POST[$this->keys[$i]] == '')
                    die($this->keys[$i].' 数据有错');
            }   /* 檢測是否數據為空 */
            $gModel = D($this->ModelName);  //相當於new一個對象出來
            $id = 0;
            if($gModel->addCampaign($id, $_POST)){
                $this->assign('jumpUrl', '?g='.GROUP_NAME.'&m='.MODULE_NAME);
                $this->success('添加成功.');
            }else{
                $this->error('添加失败');
            }
        }
        $this->assign('ur_href', '商品 &gt; 添加商品');
        $this->assign('_hash_', buildFormToken());
        $this->display('post');
    }
}