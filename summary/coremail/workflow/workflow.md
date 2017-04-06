## Workflow	[Back](./../coremail.md)

1. (开发者) 创建 `feature / fix / personl` 工作分支<br>
   组外成员可以 fork 到个人空间再创建特定分支
2. (开发者) 完成开发内容
3. (开发者) 发起合并请求 - 直接使用 GitLab 的 Merge Request 功能发送请求
4. (开发者 / 复查者 / 模块负责人) 对代码变更进行 Review 和讨论 
   1. Merge Request 里面可以执行代码相关的讨论, 并且可以陆续补充新的 commit
      - 请注意, 对引用代码的讨论要在 *"diff"* 里面进行, 不要在 *"commit"* 里面进行
      - 如果新的提交已经解决了讨论里面的问题, 请点击一下讨论里面的 (resolve) 图标   
   2. 代码 Review 过程中可能会产生很多新的 commit, 在 Review 结束时, 应执行以下步骤
      - 如果显示代码有 conflicts, 请先执行 `git rebase origin/develop` 解决冲突并 `push -f` （有额外的 review 负担)<br>
        解决冲突可能引发了新的问题, 请先回到步骤 4.1 继续 Review
      - 如果历史不需要保留, 请备注说明需要 squash, 以及 squash 之后的 commit message
      - 如果历史需要保留, 也请备注说明, 请检查每一个 commit 都是有意义的  
5. (复查者) 完成复查<br>
   1. 复查者对 Merge Request 点一下赞
   2. 生成提测包给测试者 (点一下 Deployed review environment 页面里面的 "现在构建" 按钮即可) 
   3. 把 Merge Request 分配给测试者
6. (测试者) 执行功能测试<br>
   1. 如果测试发现问题, 在 jira 中说明, 问题打回, 回到步骤 4
   2. 如果测试通过, 对 Merge Request 点一下赞, 把 Merge Request 分配给项目分支代码维护人员
7. (分支代码维护人员) 合并代码
   - 分支代码维护人员有最后的机会对代码进行审查, 如果发现问题, 也是回到步骤 4
   - 具体的合并流程参考 
     - 视乎实际问题选择直接合并（能看到分支合并过程）还是 fast forward 合并（看不到分支合并过程）<br>
       由于 [rebase / fast-forward / squash merge 都是 Gitlab EE 才有的高级功能](https://docs.gitlab.com/ee/user/project/merge_requests/)<br> 
       所以现阶段 rebase / fast forward / squash merge 都需要手工执行<br>
       一般的准则建议是, 最后合并为一个提交的, 使用 fast forward 合并<br>
       如果是复杂的问题需要保留了很多次 commit 的, 直接合并 (`--no-ff`)，使得合并可以有明确的边界
     - 手工 fast forward 合并参考命令 `git merge feature-branch --ff-only`<br>
       因为 develop 分支可能已经有了其它变化, 加参数可以提前发现错误, 手工再 rebase 一下 
     - 如果开发者之前的分支已经 `rebase` 到最新状态, 手工合并 `push` 后 Merge Request 的状态会自动变成 "已合并"
     - 否则, 代码维护人员在本地 `checkout` 后需要 `rebase` 后 `push --force` 到待合并分支, 然后 `push` 到 develop 分支<br>
       这个顺序很重要, 因为 Merge Request 是通过跟踪待合并分支的状态来工作的, 这样的先后顺序才能保证 Merge Request 能识别到问题已经合并
8. (任何人) 删除工作分支（实际上 Merge Request 本身就提供了这个操作)
6. (开发者 / 代码维护人员) Cherry Pick 变更到 XT3.0.x 分支 (假如该工作涉及到 XT3)